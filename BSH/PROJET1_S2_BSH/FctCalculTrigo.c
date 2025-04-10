//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet 2 - Calculs Trigo
// Nom du fichier 		: FctCalculTrigo.c
// Date de cr�ation 	: 14.02.2024
// Date de modification : 14.02.2024
//
// Auteur 				: Philou (Ph. Bovey)
//
// Description          : 
//
// Remarques			: voir donnee de l'�preuve            
//----------------------------------------------------------------------------------//

//-- definission pour utiliser la lib math sous VS --// 
#define _USE_MATH_DEFINES

//--- librairie standart ---//
#include <stdint.h>
#include <math.h>
//--- librairie perso ---//
#include "CalculTrigo.h"


/* ----------------------------------------------------------------------------------
// -> NOM FCT					: InitialiserStructure 
// -> PARAMETRES ENTRES			: 
// -> PARAMETRE SORTIE			: e_validation 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle 
// -> description				: tous les champs de la structure seront mis � z�ro
 ----------------------------------------------------------------------------------*/

e_validation InitialiserStructure(str_triangleRectangle* pt_strTriangle) {
	//-- d�claration variables --// 
	//-- pirmaire --// 
	static int compteur_boucle;

		//-- boucle pour initilaiser le tableau des angles --//
	for (compteur_boucle = 0; compteur_boucle <= 3; compteur_boucle++) {
		pt_strTriangle->tb_Angle[compteur_boucle] = 0;
	}

	//-- initialisation des cot�s -> adj - hyp - opp --// 
	pt_strTriangle->triangle_s.adjacent = 0;
	pt_strTriangle->triangle_s.hypotenuse = 0;
	pt_strTriangle->triangle_s.oppose = 0;

	//-- initialisation des champs de air et perim�tres --// 
	pt_strTriangle->Str_AetP.air = 0;
	pt_strTriangle->Str_AetP.perimetre = 0;

	//-- validation -> de la fct --// 
	if (memcmp(pt_strTriangle, &(str_triangleRectangle){0}, sizeof(str_triangleRectangle)) == 0) {
		return ok;
	}
	else
	{
		return nok;
	}

}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_DegRad
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en degr� -> d�terminer sa valeur 
//								  en radian 
 ----------------------------------------------------------------------------------*/
void Conversion_DegRad(str_triangleRectangle* pt_strTriangle) {
	if (pt_strTriangle->tb_Angle[0] != 0) {
		pt_strTriangle->tb_Angle[1] = (float)(pt_strTriangle->tb_Angle[0] * (M_PI / 180.0));
	}
	if (pt_strTriangle->tb_Angle[2] != 0) {
		pt_strTriangle->tb_Angle[3] = (float)(pt_strTriangle->tb_Angle[2] * (M_PI / 180.0));
	}
}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_RadDeg
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			:
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en degr� -> d�terminer sa valeur
//								  en radian
 ----------------------------------------------------------------------------------*/
void Conversion_RadDeg(str_triangleRectangle* pt_strTriangle) {
	if (pt_strTriangle->tb_Angle[1] != 0) {
		pt_strTriangle->tb_Angle[0] = (float)(pt_strTriangle->tb_Angle[1] * (180.0 / M_PI));
	}
	if (pt_strTriangle->tb_Angle[3] != 0) {
		pt_strTriangle->tb_Angle[2] = (float)(pt_strTriangle->tb_Angle[3] * (180.0 / M_PI));
	}
}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculAllAngles
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: si angle rentr� alors alors d�termine le 2�me angle 
 ----------------------------------------------------------------------------------*/
e_validation CalculerAllAngles(str_triangleRectangle* pt_strTriangle) {
	static int compteur_boucle;
	int validation = 0;

	//-- test si un angle a été défini alpha ou beta 
	if (pt_strTriangle->tb_Angle[2] != 0) {
		//-- calcul de alpha 
		pt_strTriangle->tb_Angle[0] = 90 - pt_strTriangle->tb_Angle[2];
		//-- conversion Degré -> Radian 
		Conversion_DegRad(pt_strTriangle);
	}
	if (pt_strTriangle->tb_Angle[0] != 0) {
		//-- calcul de beta
		pt_strTriangle->tb_Angle[2] = 90 - pt_strTriangle->tb_Angle[0];
		//-- conversion Degré -> Radian 
		Conversion_DegRad(pt_strTriangle);
	}

	//-- si aucun angle défini 
	if (pt_strTriangle->tb_Angle[0] == 0 && pt_strTriangle->tb_Angle[2] == 0) {
		//-- si adjacent et opposé définis -> utiliser arctan
		if (pt_strTriangle->triangle_s.adjacent != 0 && pt_strTriangle->triangle_s.oppose != 0) {
			pt_strTriangle->tb_Angle[0] = (float)(atan((float)pt_strTriangle->triangle_s.oppose / (float)pt_strTriangle->triangle_s.adjacent) * (180.0 / M_PI));
			pt_strTriangle->tb_Angle[2] = 90 - pt_strTriangle->tb_Angle[0];
		}
		//-- si adjacent et hypothénuse définis -> utiliser arccos
		else if (pt_strTriangle->triangle_s.adjacent != 0 && pt_strTriangle->triangle_s.hypotenuse != 0) {
			pt_strTriangle->tb_Angle[0] = (float)(acos((float)pt_strTriangle->triangle_s.adjacent / (float)pt_strTriangle->triangle_s.hypotenuse) * (180.0 / M_PI));
			pt_strTriangle->tb_Angle[2] = 90 - pt_strTriangle->tb_Angle[0];
		}
		//-- si opposé et hypothénuse définis -> utiliser arcsin
		else if (pt_strTriangle->triangle_s.oppose != 0 && pt_strTriangle->triangle_s.hypotenuse != 0) {
			pt_strTriangle->tb_Angle[0] = (float)(asin((float)pt_strTriangle->triangle_s.oppose / (float)pt_strTriangle->triangle_s.hypotenuse) * (180.0 / M_PI));
			pt_strTriangle->tb_Angle[2] = 90 - pt_strTriangle->tb_Angle[0];
		}
	}

	//-- test si tous les champs sont remplis 
	for (compteur_boucle = 0; compteur_boucle <= 4; compteur_boucle++) {
		if (pt_strTriangle->tb_Angle[compteur_boucle] != 0) {
			validation++;
		}
	}
	if (validation != 3) {
		return nok;
	}
	//-- retourne OK 
	return ok;
}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculerLongeursSgements
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: calculer les diff�rents segments du triangle 
//								  [adjacent - hypoth�nuse - oppos�] 
//								  selon les param�tres ins�rer par l'utilisateur
 ----------------------------------------------------------------------------------*/
e_validation CalculerLongueurSegment(str_triangleRectangle* pt_strTriangle) {

	//-- test -> si aucun angle n’est défini 
	if ((pt_strTriangle->tb_Angle[0] == 0) && (pt_strTriangle->tb_Angle[1] == 0) && (pt_strTriangle->tb_Angle[2] == 0) && (pt_strTriangle->tb_Angle[3] == 0))
	{
		//-- test si la valeur à calculer est à zéro 
		//-- calculer segment adjacent --//
		if (pt_strTriangle->triangle_s.adjacent == 0 && pt_strTriangle->triangle_s.hypotenuse != 0 && pt_strTriangle->triangle_s.oppose != 0) {
			pt_strTriangle->triangle_s.adjacent = (float)sqrt(pow((float)pt_strTriangle->triangle_s.hypotenuse, 2) - pow((float)pt_strTriangle->triangle_s.oppose, 2));
		}
		//-- calculer segment hypothénuse --// 
		if (pt_strTriangle->triangle_s.hypotenuse == 0 && pt_strTriangle->triangle_s.adjacent != 0 && pt_strTriangle->triangle_s.oppose != 0) {
			pt_strTriangle->triangle_s.hypotenuse = (float)sqrt(pow((float)pt_strTriangle->triangle_s.adjacent, 2) + pow((float)pt_strTriangle->triangle_s.oppose, 2));
		}
		//-- calculer segment opposé --//
		if (pt_strTriangle->triangle_s.oppose == 0 && pt_strTriangle->triangle_s.hypotenuse != 0 && pt_strTriangle->triangle_s.adjacent != 0) {
			pt_strTriangle->triangle_s.oppose = (float)sqrt(pow((float)pt_strTriangle->triangle_s.hypotenuse, 2) - pow((float)pt_strTriangle->triangle_s.adjacent, 2));
		}
	}

	//-- test si un angle alpha ou beta a été défini 
	if ((pt_strTriangle->tb_Angle[0] != 0) || (pt_strTriangle->tb_Angle[2] != 0)) {
		//-- test si l’angle alpha a été inséré 
		if (pt_strTriangle->tb_Angle[0] != 0) {
			//-- conversion de alpha ° -> radian 
			Conversion_DegRad(pt_strTriangle);

			//-- si hypothénuse connue
			if (pt_strTriangle->triangle_s.hypotenuse != 0) {
				//Calcul -> cos(alpha) = adj / hyp => adj = cos(alpha) * hyp
				if (pt_strTriangle->triangle_s.adjacent == 0) {
					pt_strTriangle->triangle_s.adjacent = (float)cos((float)pt_strTriangle->tb_Angle[1]) * (float)pt_strTriangle->triangle_s.hypotenuse;
				}
				//Calcul -> sin(alpha) = opp / hyp => opp = sin(alpha) * hyp
				if (pt_strTriangle->triangle_s.oppose == 0) {
					pt_strTriangle->triangle_s.oppose = (float)sin((float)pt_strTriangle->tb_Angle[1]) * (float)pt_strTriangle->triangle_s.hypotenuse;
				}
			}

			//-- si adjacent connu
			if (pt_strTriangle->triangle_s.adjacent != 0) {
				//Calcul -> hyp = adj / cos(alpha)
				if (pt_strTriangle->triangle_s.hypotenuse == 0) {
					pt_strTriangle->triangle_s.hypotenuse = pt_strTriangle->triangle_s.adjacent / (float)cos((float)pt_strTriangle->tb_Angle[1]);
				}
				//Calcul -> tan(alpha) = opp / adj => opp = tan(alpha) * adj
				if (pt_strTriangle->triangle_s.oppose == 0) {
					pt_strTriangle->triangle_s.oppose = (float)tan((float)pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.adjacent;
				}
			}

			//-- si opposé connu
			if (pt_strTriangle->triangle_s.oppose != 0) {
				//Calcul -> hyp = opp / sin(alpha)
				if (pt_strTriangle->triangle_s.hypotenuse == 0) {
					pt_strTriangle->triangle_s.hypotenuse = pt_strTriangle->triangle_s.oppose / (float)sin((float)pt_strTriangle->tb_Angle[1]);
				}
				//Calcul -> adj = opp / tan(alpha)
				if (pt_strTriangle->triangle_s.adjacent == 0) {
					pt_strTriangle->triangle_s.adjacent = pt_strTriangle->triangle_s.oppose / (float)tan((float)pt_strTriangle->tb_Angle[1]);
				}
			}
		}
	}

	//-- calcul de tous les angles -> appel de fct --// 
	CalculerAllAngles(pt_strTriangle);

	//-- check si la longueur des segments est bien calculée 
	return ok;
}









