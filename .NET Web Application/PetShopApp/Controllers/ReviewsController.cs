using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using PetShopApp.Data;
using PetShopApp.Models;
using System.Data;

namespace PetShopApp.Controllers
{
    public class ReviewsController : Controller
    {
        private readonly ApplicationDbContext db;

        private readonly UserManager<ApplicationUser> _userManager;

        private readonly RoleManager<IdentityRole> _roleManager;
        public ReviewsController(ApplicationDbContext context, UserManager<ApplicationUser> userManager,
            RoleManager<IdentityRole> roleManager)
        {
            db = context;

            _userManager = userManager;

            _roleManager = roleManager;
        }
        // Adaugarea unui comentariu asociat unui articol in baza de date
        [HttpPost]
        public IActionResult New(Review rev)
        {
            rev.Date = DateTime.Now;
            rev.UserId = _userManager.GetUserId(User);
            try
            {
                db.Reviews.Add(rev);
                db.SaveChanges();
                return Redirect("/Products/Show/" + rev.ProductId);
            }
            
            catch (Exception)
            {
                return Redirect("/Products/Show/" + rev.ProductId);
            }

        }

        // Stergerea unui comentariu asociat unui articol din baza de date
        [HttpPost]
        [Authorize(Roles = "User,Partener,Admin")]
        public IActionResult Delete(int id)
        {
            Review rev = db.Reviews.Find(id);
            if (rev.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                db.Reviews.Remove(rev);
                db.SaveChanges();
                return Redirect("/Products/Show/" + rev.ProductId);
            }
            else
            {
                TempData["message"] = "Nu aveti dreptul sa stergeti comentariul";
                return RedirectToAction("Index", "Products");
            }

        }

        // In acest moment vom implementa editarea intr-o pagina View separata
        // Se editeaza un comentariu existent

        [Authorize(Roles = "User,Partener,Admin")]
        public IActionResult Edit(int id)
        {
            Review rev = db.Reviews.Find(id);
            if (rev.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                ViewBag.Review = rev;
                return View();
            }
            else
            {
                TempData["message"] = "Nu aveti dreptul sa editati comentariul";
                return RedirectToAction("Index", "Products");
            }
            
            ;
        }

        [HttpPost]
        [Authorize(Roles = "User,Partener,Admin")]
        public IActionResult Edit(int id, Review requestReview)
        {
            Review rev = db.Reviews.Find(id);
            if (rev.UserId == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                try
                {

                    rev.Content = requestReview.Content;

                    db.SaveChanges();

                    return Redirect("/Products/Show/" + rev.ProductId);
                }
                catch (Exception e)
                {
                    return Redirect("/Products/Show/" + rev.ProductId);
                }
            }
            else
            {
                TempData["message"] = "Nu aveti dreptul sa faceti modificari";
                return RedirectToAction("Index", "Products");
            }
                

        }
    }
}
