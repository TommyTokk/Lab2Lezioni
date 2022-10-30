int main (int argc, char *argv[]) {
    

   int  x = 20; 
   
   int  *pointer = &x;  
   int a[5];
   
   for(int i  = 0; i < 5; i++){
       a[i] = i;
   }
   
   for(int i = 0; i < 5; i++){
       printf("Indirizzo di a[%d]: %p\n", i, (void *) &a[i]);
   }

   printf("Indirizzo della variabile x: %p\n", (void *) &x  );
   
   printf("Indirizzo dentro pointer: %p\n", (void *) pointer);

   printf("Valore contenuto nella cella puntata da pointer: %d\n", *pointer );

   return 0;
}