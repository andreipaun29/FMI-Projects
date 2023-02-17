using PetShopApp.Models;

namespace PetShopApp.Interfaces
{
    public interface IProductService
    {
        public IEnumerable<Product> GetProducts();
        public Product GetProduct(int sku);
    }
}
