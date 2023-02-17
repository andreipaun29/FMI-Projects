using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using PetShopApp.Data;
using PetShopApp.Models;
using System.Diagnostics;

namespace PetShopApp.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        private readonly ApplicationDbContext db;

        private readonly UserManager<ApplicationUser> _userManager;

        private readonly RoleManager<IdentityRole> _roleManager;

        public HomeController(ApplicationDbContext context,
            UserManager<ApplicationUser> userManager,
            RoleManager<IdentityRole> roleManager, 
            ILogger<HomeController> logger)
        {
            db = context;

            _userManager = userManager;

            _roleManager = roleManager;

            _logger = logger;
        }

        public IActionResult Index()
        {
            if (User.Identity.IsAuthenticated)
            {
                return RedirectToAction("Index", "Products");
            }
            var products = db.Products.Include("Category").Include("User");
            ViewBag.Products = products;

            if (TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"];
            }

            //SetAccessRights();
            return View();

        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }

        public IActionResult Show(int id)
        {
            Product product = db.Products.Include("Category").
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