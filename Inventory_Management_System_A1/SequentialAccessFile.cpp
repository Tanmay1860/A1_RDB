#include "Driver.h"
/*
* FUNCTION : menuSequentialAccess
* DESCRIPTION :
* This function displays the inventory management menu and handles user input
* for different operations like adding, viewing, updating, and deleting products.
* It runs in a loop until the user decides to exit.
*/
void menuSequentialAccess()
{
    int choice, id;
    Product product;

    while (1) {
        printf("\nInventory Management System\n");
        printf("1. Add Product\n");
        printf("2. Read Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Exit\n");
        printf("Choose an option: ");

        if (scanf_s("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;  // Restart the loop if input is invalid
        }

        clearInputBuffer();  // Clear newline character from buffer

        switch (choice) {
        case 1:  // Add Product
            printf("Enter Product ID: ");
            if (scanf_s("%d", &product.productId) != 1) {
                printf("Invalid input for Product ID.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();  // Clear newline character

            printf("Enter Name: ");
            fgets(product.name, sizeof(product.name), stdin);
            product.name[strcspn(product.name, "\n")] = 0;  // Remove newline

            printf("Enter Category: ");
            fgets(product.category, sizeof(product.category), stdin);
            product.category[strcspn(product.category, "\n")] = 0;  // Remove newline

            printf("Enter Quantity: ");
            if (scanf_s("%d", &product.quantity) != 1) {
                printf("Invalid input for Quantity.\n");
                clearInputBuffer();
                continue;
            }

            printf("Enter Price: ");
            if (scanf_s("%f", &product.price) != 1) {
                printf("Invalid input for Price.\n");
                clearInputBuffer();
                continue;
            }
            addProduct(product);
            break;

        case 2:  // Read Products
            readProducts();
            break;

        case 3:  // Update Product
            printf("Enter Product ID to update: ");
            if (scanf_s("%d", &id) != 1) {
                printf("Invalid input for Product ID.\n");
                clearInputBuffer();
                continue;
            }
            updateProduct(id);
            break;

        case 4:  // Delete Product
            printf("Enter Product ID to delete: ");
            if (scanf_s("%d", &id) != 1) {
                printf("Invalid input for Product ID.\n");
                clearInputBuffer();
                continue;
            }
            deleteProduct(id);
            break;

        case 5:  // Exit
            exit(0);
        default:
            printf("Invalid option\n");
        }
    }
    return 0;
}


// Function to add a product to the file
/*
* FUNCTION : addProduct
* DESCRIPTION :
* This function adds a new product to the inventory by writing to the binary file.
* It checks for duplicate product IDs and handles file operations.
* PARAMETERS :
* int productId : The ID of the product to be added.
* ProductSequentialAccess product : The product structure containing product details.
*/

void addProduct(Product product) {
    FILE* file;
    errno_t err = fopen_s(&file, "products.txt", "a");  // Open file in append mode
    if (err != 0) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%d,%.2f\n", product.productId, product.name, product.category, product.quantity, product.price);
    fclose(file);
    printf("Product added successfully.\n");
}

/*
* FUNCTION : readProduct
* DESCRIPTION :
* This function updates an existing product in the binary file.
* PARAMETERS :
* int position : The product ID to update.
* ProductSequentialAccess product : The updated product structure.
*/

void readProducts() {
    FILE* file;
    errno_t err = fopen_s(&file, "products.txt", "r");  // Open file in read mode
    if (err != 0) {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("\n   ProductId,Name,Category,Quantity,Price\n");
    while (!feof(file)) {
        Product product;
        if (fscanf_s(file, "%d,%49[^,],%29[^,],%d,%f\n", &product.productId, product.name, product.category, &product.quantity, &product.price) == 5) {
            printf("|%-10d  |  %-20s| %-20s |  %-10d|  $%-9.2f|\n",
                product.productId, product.name, product.category, product.quantity, product.price);
        }
    }
    fclose(file);
}

/*
* FUNCTION : updateProduct
* DESCRIPTION :
* This function updates an existing product in the binary file.
* PARAMETERS :
* int position : The product ID to update.
* ProductSequentialAccess product : The updated product structure.
*/
void updateProduct(int productId) {
    FILE* fp;
    errno_t err = fopen_s(&fp, "products.txt", "r");
    if (err != 0) {
        printf("Error opening file for reading.\n");
        return;
    }

    Product products[MAX_PRODUCTS];
    int count = 0;
    int found = 0;

    // Read existing products
    while (!feof(fp) && count < MAX_PRODUCTS) {
        fscanf_s(fp, "%d,%49[^,],%29[^,],%d,%f\n", &products[count].productId, products[count].name, products[count].category, &products[count].quantity, &products[count].price);
        count++;
    }
    fclose(fp);

    // Search for the product to update
    for (int i = 0; i < count; i++) {
        if (products[i].productId == productId) {
            found = 1;
            printf("Updating Product ID %d\n", productId);
            printf("Enter new Name: ");
            fgets(products[i].name, sizeof(products[i].name), stdin);
            products[i].name[strcspn(products[i].name, "\n")] = 0;  // Remove newline

            printf("Enter new Category: ");
            fgets(products[i].category, sizeof(products[i].category), stdin);
            products[i].category[strcspn(products[i].category, "\n")] = 0;  // Remove newline

            printf("Enter new Quantity: ");
            if (scanf_s("%d", &products[i].quantity) != 1) {
                printf("Invalid input for Quantity.\n");
                clearInputBuffer();
                return;
            }

            printf("Enter new Price: ");
            if (scanf_s("%f", &products[i].price) != 1) {
                printf("Invalid input for Price.\n");
                clearInputBuffer();
                return;
            }
            break;
        }
    }

    if (!found) {
        printf("Product ID %d not found.\n", productId);
        return;
    }

    // Rewrite the entire file with updated data
    err = fopen_s(&fp, "products.txt", "w");
    if (err != 0) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%d,%.2f\n", products[i].productId, products[i].name, products[i].category, products[i].quantity, products[i].price);
    }
    fclose(fp);
    printf("Product updated successfully.\n");
}

/*
* FUNCTION : deleteProduct
* DESCRIPTION :
* This function deletes a product from the binary file by marking it as deleted.
* PARAMETERS :
* int productId : The ID of the product to be deleted.
*/

void deleteProduct(int productId) {
    FILE* file;
    errno_t err = fopen_s(&file, "products.txt", "r");
    if (err != 0) {
        printf("Error opening file for reading.\n");
        return;
    }

    Product products[MAX_PRODUCTS];
    int count = 0;
    int found = 0;

    // Read existing products
    while (!feof(file) && count < MAX_PRODUCTS) {
        fscanf_s(file, "%d,%49[^,],%29[^,],%d,%f\n", &products[count].productId, products[count].name, products[count].category, &products[count].quantity, &products[count].price);
        count++;
    }
    fclose(file);

    for (int i = 0; i < count; i++) {
        if (products[i].productId == productId) {
            found = 1;
            printf("Deleting Product ID %d\n", productId);
            // Shift the remaining products left
            for (int j = i; j < count - 1; j++) {
                products[j] = products[j + 1];
            }
            count--;  // Reduce count
            break;
        }
    }

    if (!found) {
        printf("Product ID %d not found.\n", productId);
        return;
    }

    // Rewrite the entire file without the deleted product
    err = fopen_s(&file, "products.txt", "w");
    if (err != 0) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%d,%.2f\n", products[i].productId, products[i].name, products[i].category, products[i].quantity, products[i].price);
    }
    fclose(file);
    printf("Product deleted successfully.\n");
}


// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Read until newline or end of file
}


/*
* FUNCTION : calculateHash
* DESCRIPTION :
* This function calculates the hash position in the file for a given product ID.
* PARAMETERS :
* int productId : The ID of the product.
* RETURNS :
* int : The calculated position in the file for the product.
*/
int calculateHashRA(int productId) {
    int  position = productId * sizeof(Product);
    return position;
}

