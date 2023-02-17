using Microsoft.AspNetCore.Mvc;
using PetShopApp.Data;
using PetShopApp.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using System.Xml.Schema;

namespace PetShopApp.Controllers
{
    [Authorize]
    public class ProductsController : Controller
    {
        
        private readonly ApplicationDbContext db;

        private readonly UserManager<ApplicationUser> _userManager;

        private readonly RoleManager<IdentityRole> _roleManager;

        private readonly IWebHostEnvironment webHostEnvironment;


        public ProductsController(ApplicationDbContext context,
            UserManager<ApplicationUser> userManager,
            RoleManager<IdentityRole> roleManager,
            IWebHostEnvironment host)
        {
            db = context;

            _userManager = userManager;

            _roleManager = roleManager;

            webHostEnvironment = host;

        }

        [Authorize(Roles = "User,Partener,Admin")]
        public IActionResult Index()   
        {
            int _perPage = 3;
            var products = db.Products.Include("Category").Include("User");

            if (TempData.ContainsKey("message"))
            {
                ViewBag.message = TempData["message"].ToString();
            }
            // Fiind un numar variabil de articole, verificam de fiecare data utilizand
            // metoda Count()
            int totalItems = products.Count();
            // Se preia pagina curenta din View-ul asociat
            // Numarul paginii este valoarea parametrului page din ruta
            // /Articles/Index?page=valoare
            var currentPage = Convert.ToInt32(HttpContext.Request.Query["page"]);
            // Pentru prima pagina offsetul o sa fie zero
            // Pentru pagina 2 o sa fie 3
            // Asadar offsetul este egal cu numarul de articole care au fost deja afisate pe paginile anterioare
            var offset = 0;
            // Se calculeaza offsetul in functie de numarul paginii la care suntem
            if (!currentPage.Equals(0))
            {
                offset = (currentPage - 1) * _perPage;
            }

            // Se preiau articolele corespunzatoare pentru fiecare pagina la care ne aflam
            // in functie de offset
            var paginatedArticles = products.Skip(offset).Take(_perPage);
            // Preluam numarul ultimei pagini
            ViewBag.lastPage = Math.Ceiling((float)totalItems / (float)_perPage);
            // Trimitem articolele cu ajutorul unui ViewBag catre View-ul corespunzator
            ViewBag.Articles = paginatedArticles;

            var search = "";
            // MOTOR DE CAUTARE
            if (Convert.ToString(HttpContext.Request.Query["search"]) != null)
            {
                // eliminam spatiile libere
                search = Convert.ToString(HttpContext.Request.Query["search"]).Trim();


                // Cautare in articol (Title si Content)
                List<int> productIds = db.Products.Where
                (
                at => at.Title.Contains(search)
                || at.Description.Contains(search)
                ).Select(a => a.ProductId).ToList();
                // Cautare in comentarii (Content)
                List<int> articleIdsOfCommentsWithSearchString = db.Reviews.Where
                (
                c => c.Content.Contains(search)
                ).Select(c => (int)c.ProductId).ToList();
                // Se formeaza o singura lista formata din toate id-urile selectate anterior
                List<int> mergedIds = productIds.Union(articleIdsOfCommentsWithSearchString).ToList();
                // Lista articolelor care contin cuvantul cautat
                // fie in articol -> Title si Content
                // fie in comentarii -> Content
                products = db.Products.Where(product => mergedIds.Contains(product.ProductId))
                .Include("Category")
                .Include("User");
                }
                ViewBag.SearchString = search;
     
                if(search != "")
                {
                ViewBag.PaginationBaseUrl = "/Products/Index/?search=" + search + "&page";
                } else
                {
                ViewBag.PaginationBaseUrl = "/Products/Index/?page";
                }
                             ViewBag.Products = products;
            return View();
        }


        //[Authorize(Roles = "User,Partener,Admin")]
        public IActionResult Show(int id)
        {
            Product product= db.Products.Include("Category").
                                         Include("User").
                                         Include("Reviews").
                                         Include("Reviews.User")
                               .Where(prod => prod.ProductId == id)
                               .First();

            var n = product.Reviews.Count;
            foreach (Review rev in product.Reviews)
                product.Rating += rev.Rating;
            if (n != 0)
                product.Rating = (double)product.Rating / n;
            else
                product.Rating = 0;

            SetAccessRights();

            return View(product);
        }

        [Authorize(Roles = "Partener,Admin")]
        public IActionResult New()
        {

            Product product = new Product();

            product.Categ = GetAllCategories();

            return View(product);
        }



        [Authorize(Roles = "Partener,Admin")]
        [HttpPost]
        public IActionResult New(Product product)
        {
            product.Categ = GetAllCategories();
            product.UserId = _userManager.GetUserId(User);

            try
            {

                var uploadsFolder = Path.Combine(webHostEnvironment.WebRootPath, "images");
                var fileName = Guid.NewGuid() + "_" + product.File?.FileName;
                var filePath = Path.Combine(uploadsFolder, fileName);
                product.File?.CopyTo(new FileStream(filePath, FileMode.Create));
                product.Image = fileName;

                db.Products.Add(product);
                db.SaveChanges();
                TempData["message"] = "Produsul a fost adaugat";
                return RedirectToAction("Index");
            }
            catch(Exception e)
            {
                return View(product);
            }
        }

        [Authorize(Roles = "Partener,Admin")]
        public IActionResult Edit(int id)
        {

            Product product = db.Products.Include("Category")
                                        .Where(prod => prod.ProductId == id)
                                        .First();

            product.Categ = GetAllCategories();

            if (product.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                return View(product);
            }

            else
            {
                TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui produs care nu va apartine";
                return RedirectToAction("Index");
            }

        }

        // Se adauga articolul modificat in baza de date
        [HttpPost]
        [Authorize(Roles = "Partener,Admin")]
        public IActionResult Edit(int id, Product requestProduct)
        {
            Product product = db.Products.Find(id);
            requestProduct.Categ = GetAllCategories();

            try
            {
                if (product.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
                {
                    product.Title = requestProduct.Title;
                    product.Description = requestProduct.Description;
                    product.Price = requestProduct.Price;
                    product.Rating = requestProduct.Rating;
                    // poza?


                    product.Category = requestProduct.Category;
                    db.SaveChanges();
                    TempData["message"] = "Produsul a fost modificat";
                    return RedirectToAction("Index");
                }
                else
                {
                    TempData["message"] = "Nu aveti dreptul sa faceti modificari asupra unui produs care nu va apartine";
                    return RedirectToAction("Index");
                }

            }
            catch (Exception e)
            {
                return View(requestProduct);
            }
        }


        // Se sterge un articol din baza de date 
        [HttpPost]
        [Authorize(Roles = "Partener,Admin")]
        public ActionResult Delete(int id)
        {
            Product product = db.Products.Find(id);
            if (product.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
                {
                db.Products.Remove(product);
                db.SaveChanges();
                TempData["message"] = "Produsul a fost sters";
                return RedirectToAction("Index");
            }
            else
            {
                TempData["message"] = "Nu aveti dreptul sa stergeti un produs care nu va apartine";
                return RedirectToAction("Index");
            }
        }


        [NonAction]
        public IEnumerable<SelectListItem> GetAllCategories()
        {
            // generam o lista de tipul SelectListItem fara elemente
            var selectList = new List<SelectListItem>();

            // extragem toate categoriile din baza de date
            var categories = from cat in db.Categories
                             select cat;

            // iteram prin categorii
            foreach (var category in categories)
            {
                // adaugam in lista elementele necesare pentru dropdown
                // id-ul categoriei si denumirea acesteia
                selectList.Add(new SelectListItem
                {
                    Value = category.Id.ToString(),
                    Text = category.CategoryName.ToString()
                });
            }


            // returnam lista de categorii
            return selectList;
        }

        private void SetAccessRights()
        {
            ViewBag.AfisareButoane = false;

            if (User.IsInRole("Partener"))
            {
                ViewBag.AfisareButoane = true;
            }

            ViewBag.EsteAdmin = User.IsInRole("Admin");

            ViewBag.UserCurent = _userManager.GetUserId(User);
        }
    }
}
