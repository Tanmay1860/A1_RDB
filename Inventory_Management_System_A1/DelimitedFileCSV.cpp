#include "Driver.h"
/*
* FUNCTION : MenuDelimitedFile
* DESCRIPTION :
* This function implements a menu-driven interface for Inventory Management System.
* It allows the user to perform CRUD operations on products such us:
* 1. Adding a new product with attributes such as Product ID, Name, Category, Quantity, and Price.
* 2. Reading and displaying existing products.
* 3. Updating an existing product based on its Product ID.
* 4. Deleting a product by its Product ID.
* 
* The program uses a loop to display the menu until the user chooses to exit.
* It validates user inputs for Product ID, Name, Category, Quantity, and Price.
* Invalid inputs trigger error messages, prompting the user to provide correct data.
*/
void MenuDelimitedFile()
{
    int choice;
    int id;
    Product product;
    Product updatedProduct;
    Product products[MAX_RECORDS];
    int count;
    char buffer[50]; // Buffer for input
    int productId;
    int isNumber = 1;
 
   
    while (1) {

        printf("\nInventory Management System\n");
        printf("---------------------------\n");
        printf("\n1. Add Product\n");
        printf("2. Read Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Exit\n");
        printf("-> Choose an option: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &choice); // Parse the integer from the buffer

        switch (choice) {
        case 1:
            printf("Enter Product ID: ");
            fgets(buffer, sizeof(buffer), stdin); // Reading input as string
            sscanf(buffer, "%d", &product.productId); // Parsing integer from string

            // Validate if the produc ID is emty.
            if (buffer[0] == '\n')
            {
                printf("\n-> Invalid input: Please provide a Product ID.\n");
                break;
            }

            // Validate if the produc ID is '0'.
            if (buffer[0] == '0')
            {
                printf("\n-> Invalid input: The Product ID must be a value greater than '0'.\n");
                break;
            }
            

            printf("Enter Name: ");
            fgets(product.name, sizeof(product.name), stdin);
            product.name[strcspn(product.name, "\n")] = 0; // Remove newline
            // Validate if the produc ID is emty
            if (strlen(product.name) == 0)
            {
                printf("\n-> Invalid input: The product name is required.\n");
                break;
            }

            printf("Enter Category: ");
            fgets(product.category, sizeof(product.category), stdin);
            product.category[strcspn(product.category, "\n")] = 0;
            if (strlen(product.category) == 0)
            {
                printf("\n-> Invalid input: The product category is required.\n");
                break;
            }

            printf("Enter Quantity: ");
            fgets(buffer, sizeof(buffer), stdin);
            // Check if the input is valid and parse the quantity
            if (sscanf(buffer, "%d", &product.quantity) != 1 || product.quantity <= 0) 
            {
                printf("\n-> Invalid quantity: The product quantity must be greater than 0 and cannot be empty.\n");
                break;
            }


            printf("Enter Price: ");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%f", &product.price); // Parsing float from string
            if (sscanf(buffer, "%f", &product.price) != 1 || product.price <= 0)
            {
                printf("\n-> Invalid price: The product price must be greater than 0 and cannot be empty.\n");
                break;
            }

            addProduct(product);
            break;

        case 2:
            readProducts();
            break;

        case 3:
            printf("Enter Product ID to update: ");
            fgets(buffer, sizeof(buffer), stdin); // Reading input as string
            sscanf(buffer, "%d", &id); // Parsing integer from string

            // Validate if the produc ID to update is emty.
            if (buffer[0] == '\n')
            {
                printf("\n-> Invalid input: Please provide a Product ID.\n");
                break;
            }

            // Validate if the produc ID is '0'.
            if (buffer[0] == '0')
            {
                printf("\n-> Invalid input: The Product ID must be a value greater than '0'.\n");
                break;
            }

            printf("Enter new Name: ");
            fgets(updatedProduct.name, sizeof(updatedProduct.name), stdin);
            updatedProduct.name[strcspn(updatedProduct.name, "\n")] = 0;

            if (strlen(updatedProduct.name) == 0)
            {
                printf("\n-> Invalid input: The product name is required.\n");
                break;
            }

            printf("Enter new Category: ");
            fgets(updatedProduct.category, sizeof(updatedProduct.category), stdin);
            updatedProduct.category[strcspn(updatedProduct.category, "\n")] = 0;
            if (strlen(updatedProduct.category) == 0)
            {
                printf("\n-> Invalid input: The product category is required.\n");
                break;
            }

            printf("Enter new Quantity: ");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &updatedProduct.quantity); // Parsing integer from string
            if (sscanf(buffer, "%d", &updatedProduct.quantity) != 1 || updatedProduct.quantity <= 0)
            {
                printf("\n-> Invalid quantity: The product quantity must be greater than 0 and cannot be empty.\n");
                break;
            }


            printf("Enter new Price: ");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%f", &updatedProduct.price); // Parsing float from string
            if (sscanf(buffer, "%f", &updatedProduct.price) != 1 || updatedProduct.price <= 0)
            {
                printf("\n-> Invalid price: The product price must be greater than 0 and cannot be empty.\n");
                break;
            }

            updateProduct(id, updatedProduct);
            break;

        case 4:
            printf("Enter Product ID to delete: ");
            fgets(buffer, sizeof(buffer), stdin); // Reading input as string
            sscanf(buffer, "%d", &id); // Parsing integer from string
            deleteProduct(id);
            break;

        case 5:
            exit(0);
            break;

        default:
            printf("\n\n-> Invalid option! Please try again.\n");
        }
    }
}


/*
* FUNCTION : checkIfProductExists
* DESCRIPTION :
* This function checks whether a Product ID exists in the inventory.
*
* Parameters:
* - int productId: The Product ID to be checked for duplicity.
*
* Returns:
* - 1 if the product with the specified Product ID exists.
* - 0 if the product doesn't exist.
*
* The function begins by loading all existing products from a file into an array.
* It then iterates through the array of products, comparing each product's ID to the provided Product ID.
* If a match is found, it returns 1; if the loop completes without finding a match, it returns 0.
*/
int checkIfProductExists(int productId) 
{
    Product products[MAX_RECORDS];
    int count = loadProducts(products);  // Load existing products from the file

    // Loop through the products and check if the product ID exists
    for (int i = 0; i < count; i++) 
    {
        if (products[i].productId == productId) 
        {
            return 1;  // Product ID exists
        }
    }
    return 0;  // Product ID does not exist
}


/*
* FUNCTION : addProduct
* DESCRIPTION :
* This function adds a new product to the inventory by appending its details to a file.
*
* Parameters:
* - Product product: A structure containing the details of the product to be added, including Product ID, Name, Category, Quantity, and Price.
*
* The function first checks if the Product ID already exists in the inventory by calling `checkIfProductExists()`.
* If the ID is found to be a duplicate, an error message is displayed, and the function exits without adding the product.
*
* If the Product ID is unique, the function attempts to open the designated file in append mode.
* If the file cannot be opened, an error message is printed, and the function exits.
* If the file is successfully opened, the product details are written to the file in a comma-separated format.
* After writing, the function validates that the file is closed correctly.
* If the file closure fails, an error message is printed.
* Finally, a success message is displayed to indicate that the product was added successfully.
*/
void addProduct(Product product) 
{
    // Check if the product ID already exists
    if (checkIfProductExists(product.productId))
    {
        printf("\n***Product ID %d already exists! Please use a unique ID.***\n", product.productId);
        return;  // Exit without adding the product
    }
    FILE* file = fopen(FILENAME, "a");
    if (!file) 
    {
        printf("\nFailed to open the file in addProduct fucntion.");
        return;
    }
    fprintf(file, "%d,%s,%s,%d,%.2f\n", product.productId, product.name, product.category, product.quantity, product.price);
    // Validating the file is closing correctly. 
    if (fclose(file) != 0)
    {
        printf("\nFailed closing the file in addProduct fucntion.");
    }
    printf("\n-> Product added successfully!\n");
}


/*
* FUNCTION : readProducts
* DESCRIPTION :
* This function retrieves and displays the list of products from the inventory.
*
* The function begins by declaring an array of `Product` structures and calling `loadProducts()` to populate this array with existing product data.
* If no products are found (i.e., `loadProducts()` returns a count of 0), an informative message is printed, and the function exits.
*
* If products are found, the function prints a formatted table header displaying column names: Product ID, Name, Category, Quantity, and Price.
* It then iterates over the array of products, printing each product's details in a format.
* Each product is displayed in a table-like format with clear delineation for readability.
*
*/
void readProducts() 
{
    Product products[MAX_RECORDS];
    int count = loadProducts(products);
    if (count == 0) 
    {
        printf("\n-> No products found!\n");
        return;
    }

    printf("\n   ProductId          Name                 Category           Quantity       Price\n");
    for (int i = 0; i < count; i++) {
        printf("|------------|----------------------|----------------------|------------|------------|\n");
        printf("|%-10d  |  %-20s| %-20s |  %-10d|  $%-9.2f|\n", products[i].productId, products[i].name, products[i].category,
            products[i].quantity, products[i].price);
    }
    printf("|------------|----------------------|----------------------|------------|------------|\n");
}


/*
* FUNCTION : loadProducts
* DESCRIPTION :
* This function loads product data from a specified file into an array of `Product` structures.
*
* Parameters:
* - Product products[]: An array where the loaded products will be stored.
*
* Returns:
* - An integer representing the number of products successfully loaded. Returns 0 if no products were loaded or if the file could not be opened.
*
* The function attempts to open the designated file in read mode. If the file cannot be opened, an error message is printed, and the function returns 0.
*
* If the file is opened successfully, the function reads each line of the file, parsing product details separated by commas.
* Each product's attributes—Product ID, Name, Category, Quantity, and Price—are extracted using `strtok()` for tokenization, converting necessary strings to appropriate data types using `atoi()`and `atof()`.
* The read operation continues until either the end of the file is reached or the maximum number of records is loaded.
*
* After reading the products, the function close the file and checks for successful closure, printing an error message if the closure fails.
* Finally, the function returns the count of products loaded into the array.
*/
int loadProducts(Product products[]) 
{
    FILE* file = fopen(FILENAME, "r");
    if (!file) 
    {
        printf("\nFailed to open the file in loadProducts fucntion.\n");
        return 0;
    }

    int count = 0;
    while (fgets(products[count].name, sizeof(products[count].name), file) && count < MAX_RECORDS) 
    {
        char* token = strtok(products[count].name, ",");
        products[count].productId = atoi(token);

        token = strtok(NULL, ",");
        strcpy(products[count].name, token);

        token = strtok(NULL, ",");
        strcpy(products[count].category, token);

        token = strtok(NULL, ",");
        products[count].quantity = atoi(token);

        token = strtok(NULL, ",");
        products[count].price = atof(token);

        count++;
    }
    // Validating the file is closing correctly.
    if (fclose(file) != 0)
    {
        printf("Failed closing the file in loadProducts fucntion.\n");
    }
    return count;
}


/*
* FUNCTION : updateProduct
* DESCRIPTION :
* This function updates an existing product in the inventory based on the specified Product ID.
*
* Parameters:
* - int productId: The Product ID of the product to be updated.
* - Product updatedProduct: A structure containing the new details of the product.
*
* The function begins by loading the current products from the file into an array using the `loadProducts()` function.
* It then iterates through the array to search for the product with the specified Product ID.
* If a matching product is found, the product's details are updated with those from the `updatedProduct` structure, while retaining the original Product ID.
* A flag `found` is set to indicate that the product was successfully located and updated.
*
* After completing the search, if the product was found and updated, the modified product list is saved back to the file using the `saveProducts()` function, and a success message is displayed.
* If the product ID is not found in the inventory, an error message is printed to inform the user.
*/
void updateProduct(int productId, Product updatedProduct) 
{
    Product products[MAX_RECORDS];
    int count = loadProducts(products);
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (products[i].productId == productId) 
        {
            products[i] = updatedProduct; // Update product
            products[i].productId = productId; // Keep original ID
            found = 1;
            break;
        }
    }

    if (found) 
    {
        saveProducts(products, count);
        printf("\n-> Product updated successfully!\n");
    }
    else 
    {
        printf("\n***Product ID not found!***\n");
    }
}


/*
* FUNCTION : deleteProduct
* DESCRIPTION :
* This function delete a product from the inventory based on the specified Product ID.
*
* Parameters:
* - int productId: The Product ID of the product to be deleted.
*
* The function begins by loading the current products from the file into an array using the `loadProducts()` function.
* It then searches through the array for the product with the given Product ID.
* If a match is found, the `found` flag is set, and the remaining products are shifted left in the array to fill the gap created by the deleted product.
* The total count of products is then decremented to reflect the removal.
*
* After the deletion process, if the product was found and removed, the updated list of products is saved back to the file using the `saveProducts()` function, followed by a success message.
* If the specified Product ID is not found in the inventory, an error message is printed.
*/
void deleteProduct(int productId) 
{
    Product products[MAX_RECORDS];
    int count = loadProducts(products);
    int found = 0;

    for (int i = 0; i < count; i++) 
    {
        if (products[i].productId == productId) 
        {
            found = 1;
            // Shift remaining products left
            for (int j = i; j < count - 1; j++) 
            {
                products[j] = products[j + 1];
            }
            count--; // Reduce the count of products
            break;
        }
    }

    if (found) 
    {
        saveProducts(products, count);
        printf("\n-> Product deleted successfully!\n");
    }
    else 
    {
        printf("\nProduct ID not found!\n");
    }
}


/*
* FUNCTION : saveProducts
* DESCRIPTION :
* This function saves an array of products to a specified file, overwriting any existing content.
*
* Parameters:
* - Product products[]: An array of `Product` structures to be saved.
* - int count: The number of products to be saved in the file.
*
* The function attempts to open the designated file in write mode. If the file cannot be opened, an error message is printed, and the function exits without saving.
*
* If the file is successfully opened, the function iterates over the provided array of products, writing each product's details in a comma-separated format.
* Each product's attributes—Product ID, Name, Category, Quantity, and Price—are formatted for output using `fprintf()`.
*
* After writing all products, the function close the file and checks for successful closure, printing an error message if the closure fails.
*/
void saveProducts(Product products[], int count) 
{
    FILE* file = fopen(FILENAME, "w");
    if (!file) 
    {
        printf("\nFailed to open file in saveProducts fucntion\n");
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        fprintf(file, "%d,%s,%s,%d,%.2f\n", products[i].productId, products[i].name, products[i].category, products[i].quantity, products[i].price);
    }
    // Validating the file is closing correctly.
    if (fclose(file) != 0)
    {
        printf("Failed closing the file in saveProducts fucntion.\n");
    }
}
