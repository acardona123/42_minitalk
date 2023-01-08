#include <stdio.h>
#include <stdlib.h>

int main()
{
	long long int l;

	l = atoi("-1");
	l = l << 1;
	l+= 1;

	printf("%lld", l >> 1);
	return ("Erreur", 1);
}

//gcc essai_bitshift_neg.c -o test && ./test && rm test