using Microsoft.AspNetCore.Mvc;

namespace PetShopApp.Controllers
{
    public class RequestsController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
