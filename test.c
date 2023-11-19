#include <stdio.h>
#include <string.h>

// Struct for storing product data
typedef struct {
    char Name[50];
    float Price;
    int Quantity;
}Product;

// Struct for storing order data
typedef struct {
    int Id;
    // Product array to store the data of several products in a single order
    Product Products[99];
    float Total;
}Order;

int main() {
    // Creating an array to store multiple orders
    Order orders[99];

    /*
    id = Will be used as an iteration variable, to go from order to order;
    status = Will determine whether the program should continue running;
    c = Will be used to clear the keyboard buffer.
    */
    int id = 0, status = 1, c;

    while (status) {
        // Cleaning the screen
        printf("\e[1;1H\e[2J");

        // Shows the options menu and asks for an input
        printf("1 - New order");
        printf("\n2 - List order(s)");
        printf("\n3 - Exit");
        printf("\nChoose an option: ");
        int option;
        scanf("%d", &option);

        switch (option){
            // If the user chooses option 1...
            case 1:
                printf("\e[1;1H\e[2J");

                printf("ORDER ID: %d", id + 1);
                printf("\n======================================");
                // Assigns the value of the current id to the current order
                orders[id].Id = id;

                // Will store the value of each request
                float total = 0;

                for (int i = 0; i < 99; i++) {
                    // Clears the keyboard buffer (character '\n' from the last input operation)
                    while ((c = getchar()) != '\n' && c != EOF);

                    printf("\n#Product %d", i + 1);
                    
                    // Collects data on each product
                    printf("\nEnter the name of the product: ");    
                    char name[50];
                    fgets(name, sizeof(name), stdin);

                    printf("\nEnter the price of the product: ");
                    float price;
                    scanf("%f", &price);

                    printf("\nEnter the quantity of the product: ");
                    int quantity;
                    scanf("%d", &quantity);
                    
                    // Creates a temporary/local instance of a product
                    Product product = {.Price = price, .Quantity = quantity};
                    strcpy(product.Name, name);
                    
                    // Adds the created product to the corresponding order
                    orders[id].Products[i] = product;

                    total += price * quantity;

                    printf("\nDo you want to add another product? [y/n] ");
                    char newProduct;
                    scanf(" %c", &newProduct);
                    
                    if (newProduct != 'y') {
                        break;
                    }

                    printf("-------------------------------------------");

                }
                orders[id].Total = total;
                id++;
                break;
            // If the user chooses option 2...
            case 2:
                printf("\e[1;1H\e[2J");
                
                // Will store the value of all orders
                float overallTotal = 0;

                // These 2 "for" loops will list all the orders
                for (int i = 0; i < id; i++) {
                    if (i > 0) {
                        printf("\n");
                    }
                    printf("ORDER ID: %d", i + 1);
                    for (int j = 0; j < 99; j++) {
                        printf("\n----------------------------------");
                        printf("\n#Product %d", j + 1);
                        printf("\nProduct's name: %s", orders[i].Products[j].Name);
                        printf("Product's price: %f", orders[i].Products[j].Price);
                        printf("\nProduct's quantity: %d", orders[i].Products[j].Quantity);

                        /*
                        Stops listing products when the quantity of the next product is 0
                        (this means that in the next position of the Products array there is no product).
                        */
                        if (orders[i].Products[j + 1].Quantity == 0) {
                            break;
                        }
                    }
                    // Shows the order total
                    printf("\n==================================");
                    printf("\nTotal: %f", orders[i].Total);
                    overallTotal += orders[i].Total;
                    printf("\n==================================\n");
                }
                // Shows the total of all orders
                printf("\n- Overall total: %f\n", overallTotal);
                printf("\nPress any key to continue...");
                // Clears the keyboard buffer (character '\n' from the last input operation)
                while ((c = getchar()) != '\n' && c != EOF);
                // Reads any key to proceed
                getchar();
                break;
            // If the user chooses option 3...
            case 3:
                // Ends the program
                status = 0;
                break;
        }
    }
  
    return 0;
}
