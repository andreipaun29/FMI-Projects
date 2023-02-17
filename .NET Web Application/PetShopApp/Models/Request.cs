using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using SelectListItem = Microsoft.AspNetCore.Mvc.Rendering.SelectListItem;

namespace PetShopApp.Models
{
    public class Request
    {
        public string? UserId { get; set; }
        public virtual ApplicationUser User { get; set; }
        [Key]
        public int Id { get; set; }
        [Required(ErrorMessage = "Titlul este obligatoriu")]
        [StringLength(100, ErrorMessage = "Titlul nu poate avea mai mult de 100 de caractere")]
        [MinLength(5, ErrorMessage = "Titlul trebuie sa aiba mai mult de 5 de caractere")]
        public string Title { get; set; }

        [Required(ErrorMessage = "Descrierea produsului este obligatorie")]
        public string Description { get; set; }

        public string? Image { get; set; }

        [Range(1, 100000, ErrorMessage = "Pretul trebuie sa fie mai mare decat 0")]
        public int Price { get; set; }

        public double Rating { get; set; }


        public int? CategoryId { get; set; }
        public virtual Category? Category { get; set; }

        [NotMapped]
        public IEnumerable<SelectListItem>? Categ { get; set; }


        [Required(ErrorMessage = "Imaginea e obligatorie")]
        [NotMapped]
        public IFormFile? File { get; set; }

    }
}
