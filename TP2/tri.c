#include "tri.h"

void bulle (int k) 
{
	int tmp,i;
	for (i=1 ; i<=k ; i++) 
	{ 
		if (t.valeurs[i] > t.valeurs[i-1]) // echange de t[i] et t[i+1]
		{
			tmp = t.valeurs[i];
			t.valeurs[i] = t.valeurs[i-1];
			t.valeurs[i-1] = tmp;
		}
	}
}

void trier ()
{
	int i=0 ;
	for (i=t.taille-1 ; i>=0 ; i--) 
	{
		bulle (i);
	}
}
