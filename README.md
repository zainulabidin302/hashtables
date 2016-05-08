#Hashtable Performance Analysis

## Zain Ul Abidin

This repository compares different types of hashtables implementations. 

 
 
  As perfect hashing is very hard to implement, their is a need for collision resolution if 
we are usure about the collisions. For this purpose we use two types of techniques.


 * Closed Hashing (Open Addressing)
  There are a number of techniques which we can use in open addressing to resolve collisions. Following is a brief overview.
   (If you find any other, help me to add it to this repo so we will have a common place for implementation for others )
    * Linear Hashtable
      This implemetation use linear probing for collision resolution.
       While this is the most easy technique to resolve the collision.
    * Quadratic Hashtable
      This implemetation use quadratic probing for collision resolution.
    * Logarithmic Hashtable
      This implemetation use logarithemic probing for collision resolution.
    * Double Hashtable
      This implemetation use double probing for collision resolution.
      


 * Open Hashing (Separate Chaining)

 
I have added a collidable hashtable also, so incase you want to test your hash function for certain data, you can use it and just override the hash function.


 
  
  
