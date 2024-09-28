/*
* File : main.cpp
* Project: File Management System
* Programmers: Juan Jose Bejarano and Brayan Rojas
* First version: 27/09/2024
* Description:
* This program serves as the main entry point for a file management system,
* allowing users to interact with different types of file access methods including
* delimited files (CSV), random access files, and a placeholder for sequential access files.
*/
#ifndef DRIVER_H
#define DRIVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // required by Visual Studio

#define MAX_RECORDS 100
#define RECORD_SIZE 256
#define FILENAME "products.csv"


typedef struct {
    int productId;
    char name[50];
    char category[50];
    int quantity;
    float price;
} Product;


// Function Prototypes
void addProduct(Product product);
void readProducts();
void updateProduct(int productId, Product updatedProduct);
void deleteProduct(int productId);
void saveProducts(Product products[], int count);
int loadProducts(Product products[]);
void MenuDelimitedFile();
int checkIfProductExists(int productId);


#endif