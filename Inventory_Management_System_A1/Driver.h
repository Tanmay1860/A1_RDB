#ifndef DRIVER_H
#define DRIVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // required by Visual Studio

#define MAX_RECORDS 100
#define RECORD_SIZE 256
#define FILENAME "products.csv"
#define FILENAMERA "product.dat"


typedef struct {
    int productId;
    char name[50];
    char category[50];
    int quantity;
    float price;
} Product;


// Function Prototypes for Delimited File CSV
void addProduct(Product product);
void readProducts();
void updateProduct(int productId, Product updatedProduct);
void deleteProduct(int productId);
void saveProducts(Product products[], int count);
int loadProducts(Product products[]);
void MenuDelimitedFile();
int checkIfProductExists(int productId);

// Function Prototypes for RandomAccessFiles
void addProductRA(int productId, Product product);
Product searchProductByPositionRA(int productId);
void updateProductRA(int productId, Product product);
void deleteProductRA(int productId);
int calculateHashRA(int productId);
void loadProductsRA();
void menuRandomAccess();

#endif