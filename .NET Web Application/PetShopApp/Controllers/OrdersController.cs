using Microsoft.AspNetCore.Mvc;

namespace PetShopApp.Controllers
{
    public class OrdersController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
