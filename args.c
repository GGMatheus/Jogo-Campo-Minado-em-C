#include <stdio.h>
#include<string.h>
#include <stdlib.h>

/* comentario 
   multi
   linha */


int main (int argc, char **argv) /* comentario multi
linha apos codigo */
{
	// comentario de uma linha
	char str[] = "ololo";
	for (int i = 0; i < 6; i++) {
		if (str[i]) {
			printf("%c\n", str[i]);	
		}
		else {
			printf("barra 0 == NULL\n");
		}
	}

	char *k;
	k = malloc(sizeof(char));
	*k = '\0';

	if (!*k) {
		printf("barra zero é falso\n");
	}

	if (*k == NULL) {
		printf("barra zero é nulo\n");
	}
	// mais
	// uns /* multi linha de mentira */

	// comentarios ai
	/* comentario multi linha em uma linha */
	/* olha aqui mais um
	multi linha */

}