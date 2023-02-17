using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using PetShopApp.Models;

namespace PetShopApp.Data
{
    public class ApplicationDbContext : IdentityDbContext<ApplicationUser>
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        public DbSet<ApplicationUser> ApplicationUsers { get; set; }
        public DbSet<Product> Products { get; set; }
        //public DbSet<User> Users { get; set; }
        //public DbSet<Role> Roles { get; set; }
        public DbSet<Review> Reviews { get; set; }
        public DbSet<Category> Categories { get; set; }

        public DbSet<Cart> Carts { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {

            base.OnModelCreating(modelBuilder);

            // definire primary key compus
            modelBuilder.Entity<Cart>()
                .HasKey(ab => new { ab.CartID, ab.ProductId, ab.UserId });


            // definire relatii cu modelele Bookmark si Article (FK)
            modelBuilder.Entity<Cart>()
                .HasOne(ab => ab.Product)
                .WithMany(ab => ab.Carts)
                .HasForeignKey(ab => ab.ProductId);

            modelBuilder.Entity<Cart>()
                .HasOne(ab => ab.User)
                .WithMany(ab => ab.Carts)
                .HasForeignKey(ab => ab.UserId);
        }

    }
}