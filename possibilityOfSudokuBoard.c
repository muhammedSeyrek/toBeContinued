#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array[9][9];
int temp[9][9];
int deep[1000][9][9];
int zeroCount = 0;
int variationCount = 0; 

int check(int number, int x, int y) {
    for (int i = 0; i < 9; i++) 
        if (array[x][i] == number || array[i][y] == number) 
            return 0;
            
    int startX = x - (x % 3);
    int startY = y - (y % 3);
    for (int i = startX; i < startX + 3; i++) 
        for (int j = startY; j < startY + 3; j++) 
            if (array[i][j] == number) 
                return 0;
                
    return 1;
}

int fillSudoku(int x, int y){
    if (x == 9) {
    	x = 0;
        if (++y == 9) {
            return 1; 
        }
    }
    
    if (array[x][y] != 0) {
        return fillSudoku(x + 1, y);
    }
    
    for (int num = 1; num <= 9; num++) {
        if (check(num, x, y)){
            array[x][y] = num;
            if (fillSudoku(x + 1, y)){
                return 1;
            }
            array[x][y] = 0; 
        }
    }
    return 0;
}

void print(){
	for(int k = 0; k < 1000; k++){
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 9; j++){
				printf("%d ", deep[k][i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
}

int randFill(int x, int y){
	if (y == 9) {
    	y = 0;
        if (++x == 9) {
            return 1; 
        }
    }
    
    if (array[x][y] != 0) {
        return fillSudoku(x, y + 1);
    }
    int num;
    do{
    	num = rand() % 9 + 1;
	}
    while (check(num, x, y));
    array[x][y] = num;
    if (fillSudoku(x, y + 1)){
        return 1;
    }
    array[x][y] = 0; 
    return 0;
}

void tempToArray(){
	for (int i = 0; i < 9; i++) {
	    for (int j = 0; j < 9; j++) {
	        array[i][j] = temp[i][j]; 
	    }
	}
}

void arrayFillZero(){
	for (int k = 0; k < 9; k++) {
        for (int j = 0; j < 9; j++) {
            array[k][j] = 0;
        }
    }
}

void deepFillZero(int i){
	for(int j = 0; j < 9; j++){
		for(int k = 0; k < 9; k++){
			deep[i][j][k] = 0;
		}
	}
}

void countZeros(){
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			if(temp[i][j] == 0)
				zeroCount++;
}

void fillZeroAndArrayToTemp(){
	for(int i = 0; i < 9; i++) 
        for(int j = 0; j < 9; j++) {
            array[i][j] = 0;
            temp[i][j] = 0; 
        }
        
    while(!fillSudoku(0, 0)){} // Burda ilk temp kismini dolduruyorum.
    for(int i = 0; i < 9; i++)
    	for(int j = 0; j < 9; j++)
    		temp[i][j] = array[i][j];
}

int main() {
    srand(time(NULL));
    fillZeroAndArrayToTemp(); //Bu kisimda iclerini bosaltiyorum. Ve tahtayi dolduruyorum.
    
    for(int i = 0; i < 9; i++){
    	int index = rand() % 2;
    	for(int j = index; j < 9; j++){
    		temp[i][j] = 0; //random olarak bosaltiyorum bazi kisimlarini.
    		j += rand() % 2;
		}
	}
	
	for(int i = 0; i < 9; i++){
    	for(int j = 0; j < 9; j++){
    		printf("%d ", temp[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	
	countZeros(); //sudoku tahtamdaki sifirlar sayilsin.
    tempToArray(); //array'e aktariyorum.
    
    for (int i = 0; i < 1000; ){
    	if(randFill(0, 0)){ //yarim olan arrayi tekrar dolduruyorum.
    		for(int j = 0; j < 9; j++){
	    		for(int k = 0; k < 9; k++){
	    			deep[i][j][k] = array[j][k]; //deep kismina atayip karsilastiricam.
				}
			}
			i++;
		}
		else{
			arrayFillZero(); //array'i sifirla.
	    	tempToArray(); //array'e temp'i at.
		}
	}
	
	print();
    
    int kind = 1; // farkli oldukca arttir.
    float prob = 0.0; // olasiligini hesapla.
    for (int i = 0; i < 1000; i++)
	    for (int j = i + 1; j < 1000; j++){
	    	int distinctCount = 0;
	    	if(deep[i][0][0] == 0) //basina isaret konulan onceden ustunden gecilmis olan kisim.
	    		break;
	    	if(deep[j][0][0] == 0) //basina isaret konulan onceden ustunden gecilmis olan kisim.
	    		break;
	    	for(int x = 0; x < 9; x++){
	        	for(int y = 0; y < 9; y++)
	                if (deep[i][x][y] == deep[j][x][y]){
	                	distinctCount++; // elemanlar benzedikce arttir.
					}
			}
			if(distinctCount < 81) // 81 olsaydi ayni olacaklardi.
				kind++;
			else
				deepFillZero(j); // o dizinin indexini sifirla.
				
			//Olasilik Hesaplarini yapan kisim.
			if(i > 0)
				prob = ((prob + ((float)(i + 1) / (float)kind)) / 2.0); 
			else
				prob = (float)(i + 1) / (float)kind;
		}
		
	// Durumlari yazdirma kismi.
	printf("\nZero Count = %d\n", zeroCount);
	printf("\n\nCount = %d\n", kind);
	printf("\n\nProbability = %.2f", prob);
	return 0;
}

