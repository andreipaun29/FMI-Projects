
using PetShopApp.Models;
namespace PetShopApp.Models
{

    public class Product_Item
    {
        public Product Product { get; set; }
        public int Quantity { get; set; }

        private decimal _SubTotal;
        public decimal SubTotal
        {
            get { return _SubTotal; }
            set { _SubTotal = Product.Price * Quantity; }
        }
    }
}
