# Programming Assignment 2

The project models a very simplified version of an online retail system such as Amazon. It will read a database of products from certain categories as well as users and their associated information, and it allows a user to interactively search for products based on certain keywords returning the products that match the search. From those matches,  this program will allow a user to add select items to their “cart”, view items in their cart, purchase the items in their cart, and save the updated database of product and user information.

There three main catagories of data in the datastore.

## Products 
There are three types of product for now: book, clothing, and movie
The common information they all contain includes price and quantity

### Book
contains information including name, author, isbn

### Clothing
contains information including name, brand, size

### Movie
contains information including name, genre, rating

## Users
each user contains information including username, balance, and type (which is not used for this assignment)

## Carts
each user has a cart 

### AddToCart
users can add a "hit" to their carts from the most recent search

### ViewCart
users can view their cart by showing all the items in the order they added the hits

###
users can buy the products (in FIFO order) in their cart if the product is in stock and they have enough balance
