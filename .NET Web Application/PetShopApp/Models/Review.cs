using System.ComponentModel.DataAnnotations;

namespace PetShopApp.Models
{
    public class Review
    {
        public string? UserId { get; set; }
        public virtual ApplicationUser User { get; set; }
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Continutul este obligatoriu")]
        public string Content { get; set; }

        [Required(ErrorMessage = "Ratingul este obligatoriu")]
       public int Rating { get; set; }
        public DateTime Date { get; set; }

        public int ProductId { get; set; }

        public virtual Product Product { get; set; }
    }
}
