﻿using System.ComponentModel.DataAnnotations.Schema;

namespace PetShopApp.Models
{
    public class Cart
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int CartID { get; set; }
        public int? ProductId { get; set; }
        public string? UserId { get; set; }
        public int Quantity { get; set; }
        public virtual Product? Product { get; set; }
        public virtual ApplicationUser? User { get; set; }

        //public virtual Profile? User { get; set; }
    }
}
