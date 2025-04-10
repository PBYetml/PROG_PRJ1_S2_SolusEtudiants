//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet 2 - Calculs Trigo
// Nom du fichier 		: mainProjet1_s2.c
// Date de création 	: jsp 
// Date de modification : 10.04.2024
//
// Auteur 				: Hayatache ( benjamin schafroth ) 
//
// Description          : 
//
// Remarques			: voir donnee de l'épreuve            
//----------------------------------------------------------------------------------//
//-- directive préprocesseur pour supprimer certains warining --//
#pragma warning(disable : 4996)		//-- warning concernant les scanf

//--- librairie standart ---//
#include <stdio.h>                  // entrée - sortie
#include <stdlib.h>					// fonctions système 
#include <stdint.h>

//--- librairie perso ---//
#include "CalculTrigo.h"

//-- déclaration de constantes --// 
const char* ptNOM_CANDIDAT = "Benjamin Schafroth"; 
const char VERSION_PROJET = 2; 
const unsigned short ANNEE_TEST = 2025; 


//-- programme principal --// 
void main()
{
	//-- déclaration de variables locales --//
	//-- enumération 
	e_choixCoteAngle choix_C_A;
	e_choixCote choix_AHC;
	e_choixAngle choix_AB; 
	e_validation testFct = nok; 
	

	//-- type primaire 
	char nbChoix = 0; 
	char longueurSegment; 
	float angle_deg; 

	//-- variable structure -> A IMPLEMENTER 
	// triangle

	//-- message utilisateur --// 
	printf("-- TEST n%02d - annee : %d - Nom Candidat : %s --\n", VERSION_PROJET, ANNEE_TEST, ptNOM_CANDIDAT); 
	printf("\n");
	printf("\n -> taille en memoire de la structure Triangle en theorie : 24 [0]");
	printf("\n");
	printf("\n -> taille en memoire de la structure Triangle en pratique : %d [0]",sizeof(str_triangleRectangle));
	printf("\n");

	//-- msg -> taille structure -> A IMPLEMENTER --// 
	//printf("\n-> taille en memoire de la structure triangle : [o] \n", );
	
	//-- initialisation de la structure -> A IMPLEMENTER --//
	str_triangleRectangle Triangle={0};
	testFct = InitialiserStructure(&Triangle);

	//-- msg user & selection valeur --// 
	//-- itération -> max 2 choix possible 
	while ((testFct == ok) && (nbChoix < NB_CHOIX_MAX))
	{
		printf("\n=> choix de selection entrez : 0 -> pour cote | 1 -> pour angle : ");
		scanf("%d", &choix_C_A);

		//-- nettoyer le bufferclavier --// 
		while ((getchar() != '\n') && (getchar() != EOF));

		//--> choix de la séquence de sélection 
		switch (choix_C_A)
		{
			case cote:
				//-- msg user pour sélection --// 
				printf("\n=> choix du cote, entrer : 1 -> pour adj | 2 -> pour hyp | 3 -> pour opp :  "); 
				scanf("%d", &choix_AHC);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- msg user pour inserer une valeur de longeur 
				printf("\n=> inserez une valeur entre 1 et 100  : "); 
				scanf("%d", (int*)&longueurSegment); 
							
				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- test de la sélection + maj structure triangle  
				//-> adjacent
				if (choix_AHC == adj)
					//MAJ variable triangle -> champs : adjacent -> A IMPLEMENTER
					Triangle.triangle_s.adjacent = longueurSegment;
				//-> hypothénuse
				else if (choix_AHC == hyp)
					//MAJ variable triangle -> champs : hypthénuse -> A IMPLEMENTER
					
					Triangle.triangle_s.hypotenuse = longueurSegment;
				//-> opposé 
				else 
					//MAJ variable triangle -> champs : opposé  -> A IMPLEMENTER
					Triangle.triangle_s.oppose = longueurSegment;
				
				//-- MAJ de nb de choix à disposition --// 
				nbChoix++; 

				break;

			case angle:
				//-- msg user pour sélection --// 
				printf("\n=> choix de l'angle, entrer : 1 -> pour Alpha | 2 -> pour Beta :  ");
				scanf("%d", &choix_AB);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- msg user pour inserer une valeur d'angle 
				printf("\n=> inserez une valeur entre 0.1 et 90.0 degré : ");
				scanf("%f", &angle_deg);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- test de la sélection + maj structure triangle  
				if (choix_AB == alpha)
					//-- MAJ de l'angle Alpha -> case 0 -> A IMPLEMENTER
					Triangle.tb_Angle[0] = angle_deg;

				else
					//-- MAJ de l'angle Beta -> case 2 -> A IMPLEMENTER
					Triangle.tb_Angle[2] = angle_deg;

				//-- MAJ de nb de choix à disposition --// 
				nbChoix++;

				break;

			default:
				printf("\n !! Aucune valeur n'a ete choisie !! "); 
				break;
		}
	}

	//-- appel de fct pour le calcul des segments -> A IMPLEMENTER
	//testFct = ... 
	testFct = CalculerLongueurSegment(&Triangle);

	//-- msg user - état calcul --// 
	if (testFct == ok)
	{
		//-- Affichage à implémenter !!! 
		printf("\n");
		printf("\n -> Resultats : longeur adjacent %d",Triangle.triangle_s.adjacent);
		printf("\n -> Resultats : longeur hypothenuse  %d", Triangle.triangle_s.hypotenuse);
		printf("\n -> Resultats : longeur oppose  %d", Triangle.triangle_s.oppose);
		printf("\n -> Resultats : angle alpha %.2f", Triangle.tb_Angle[0]);
		printf("\n -> Resultats : angle beta  %.2f", Triangle.tb_Angle[2]);
		printf("\n");
	}
	else
		printf("\n -> erreur de calcul !!!"); 

	//-> pause -> system
	system("pause"); 
}