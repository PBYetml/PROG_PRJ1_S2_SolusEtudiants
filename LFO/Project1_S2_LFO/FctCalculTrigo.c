//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet 2 - Calculs Trigo
// Nom du fichier 		: FctCalculTrigo.c
// Date de création 	: 14.02.2024
// Date de modification : 14.02.2024
//
// Auteur 				: Philou (Ph. Bovey)
//
// Description          : 
//
// Remarques			: voir donnee de l'épreuve            
//----------------------------------------------------------------------------------//

//-- definission pour utiliser la lib math sous VS --// 
#define _USE_MATH_DEFINES

//--- librairie standart ---//


//--- librairie perso ---//
#include "CalculTrigo.h"
#include <math.h>

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: InitialiserStructure 
// -> PARAMETRES ENTRES			: 
// -> PARAMETRE SORTIE			: e_validation 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle 
// -> description				: tous les champs de la structure seront mis à zéro
 ----------------------------------------------------------------------------------*/
e_validation InitialiserStructure(str_triangleRectangle* pt_strTriangle)
{
	//-- déclaration variables --// 
	//-- pirmaire --// 
	uint8_t i = 0;

	//-- enumeration --// 
	e_validation checkFct = nok;

	//-- boucle pour initilaiser le tableau des angles --//
	for (i = 0; i < TAILLE_TB_ANGLE; i++)
	{
		pt_strTriangle->tb_Angle[i] = 0;
	}
	//-- initialisation des cotés -> adj - hyp - opp --// 
	pt_strTriangle->triangle_s.adjacent = 0;
	pt_strTriangle->triangle_s.hypotenuse = 0;
	pt_strTriangle->triangle_s.oppose = 0;

	//-- initialisation des champs de air et perimètres --// 
	pt_strTriangle->air = 0;
	pt_strTriangle->perimetre = 0;

	//-- validation -> de la fct --// 
	if (
		(pt_strTriangle->tb_Angle[0] == 0) &&
		(pt_strTriangle->tb_Angle[1] == 0) &&
		(pt_strTriangle->tb_Angle[2] == 0) &&
		(pt_strTriangle->tb_Angle[3] == 0) &&
		(pt_strTriangle->triangle_s.adjacent == 0) &&
		(pt_strTriangle->triangle_s.hypotenuse == 0) &&
		(pt_strTriangle->triangle_s.oppose == 0) &&
		(pt_strTriangle->air == 0) &&
		(pt_strTriangle->perimetre == 0)
		)
	{
		checkFct = ok;
	}

	//-- valeur à retourner --// 
	return checkFct;
}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_DegRad
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en degré -> déterminer sa valeur 
//								  en radian 
 ----------------------------------------------------------------------------------*/
void Conversion_DegRad(str_triangleRectangle* pt_strTriangle)
{
	//-- test si angle à convertir --//
	//--> alpha 
	if (pt_strTriangle->tb_Angle[0] != 0) 
		pt_strTriangle->tb_Angle[1] = (pt_strTriangle->tb_Angle[0] * M_PI) / 180;

	//--> beta 
	else if (pt_strTriangle->tb_Angle[2] != 0) 
		pt_strTriangle->tb_Angle[3] = (pt_strTriangle->tb_Angle[2] * M_PI) / 180;

}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_RadDeg
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			:
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en radian -> déterminer sa valeur
//								  en degré
 ----------------------------------------------------------------------------------*/
void Conversion_RadDeg(str_triangleRectangle* pt_strTriangle)
{
	//-- test si angle à convertir --//
	//--> alpha 
	if (pt_strTriangle->tb_Angle[1] != 0)
		pt_strTriangle->tb_Angle[0] = (pt_strTriangle->tb_Angle[1] * 180) / M_PI;

	//--> beta 
	else if (pt_strTriangle->tb_Angle[3] != 0)
		pt_strTriangle->tb_Angle[2] = (pt_strTriangle->tb_Angle[3] * 180) / M_PI;

}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculAllAngles
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: si angle rentré alors alors détermine le 2ème angle 
 ----------------------------------------------------------------------------------*/
e_validation CalculerAllAngles(str_triangleRectangle* pt_strTriangle)
{
	uint8_t i;
	e_validation checkFct = nok;

	//-- test si un angle a été définit alpha ou beta 
	if ((pt_strTriangle->tb_Angle[0]) || (pt_strTriangle->tb_Angle[2])) {
		//-- calcul de alpha 
		if (pt_strTriangle->tb_Angle[2]) 
			pt_strTriangle->tb_Angle[0] = 90 - (pt_strTriangle->tb_Angle[2]);

		//-- calcul de beta
		else if (pt_strTriangle->tb_Angle[0])
			pt_strTriangle->tb_Angle[2] = 90 - (pt_strTriangle->tb_Angle[0]);

			Conversion_DegRad(pt_strTriangle);	//-- conversion Degré - Radian 
	}
	else {
		//-- si pas d'angle défini 

			//-- si coté non défini -> hypothénuse -> fonction trigo inversée arctan 
		if (pt_strTriangle->triangle_s.hypotenuse == 0) {
			pt_strTriangle->tb_Angle[1] = (float)atan(((double)(pt_strTriangle->triangle_s.adjacent) / (pt_strTriangle->triangle_s.oppose)));
			//-- conversion Radian - Degré 
			Conversion_RadDeg(pt_strTriangle);
			pt_strTriangle->tb_Angle[2] = 90 - (pt_strTriangle->tb_Angle[0]);
			
		}
			//-- si coté non défini -> opposé -> fonction trigo inversée arccos
		else if (pt_strTriangle->triangle_s.oppose == 0) {
			pt_strTriangle->tb_Angle[1] = (float)acos(((double)(pt_strTriangle->triangle_s.oppose) / (pt_strTriangle->triangle_s.hypotenuse)));
			//-- conversion Radian - Degré 
			Conversion_RadDeg(pt_strTriangle);
			pt_strTriangle->tb_Angle[2] = 90 - (pt_strTriangle->tb_Angle[0]);
		}
			//-- si coté non défini -> adjacent -> fonction trigo inversée arcsin
		else if (pt_strTriangle->triangle_s.adjacent == 0) {
			pt_strTriangle->tb_Angle[1] = (float)asin(((double)(pt_strTriangle->triangle_s.adjacent) / (pt_strTriangle->triangle_s.hypotenuse)));
			//-- conversion Radian - Degré 
			Conversion_RadDeg(pt_strTriangle);
			pt_strTriangle->tb_Angle[2] = 90 - (pt_strTriangle->tb_Angle[0]);
		}

	}

		
	//-- test si tous les champs sont remplis 
	for (i = 0; i < TAILLE_TB_ANGLE; i++)
	{
		if (pt_strTriangle->tb_Angle[i] == 0.0) {
			checkFct = nok;
			i = TAILLE_TB_ANGLE;	//forcer à sortire de la boucle pour retourner une erreur
		}
		else
			checkFct = ok;
			
	}
		//-- retourne OK 
	return checkFct;
}


/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculerLongeursSgements
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: calculer les différents segments du triangle 
//								  [adjacent - hypothénuse - opposé] 
//								  selon les paramètres insérer par l'utilisateur
 ----------------------------------------------------------------------------------*/
e_validation CalculerLongueurSegment(str_triangleRectangle* pt_strTriangle)
{
	uint8_t i;
	e_validation checkFct = nok;


	//-- calcul de tous les angles -> appel de fct --// 
	CalculerAllAngles(pt_strTriangle);

	//-- test si un angle a été définit alpha ou beta 
	if ((pt_strTriangle->tb_Angle[0]) || (pt_strTriangle->tb_Angle[2])) {
		//-- test si l'angle alpha a été inséré 
		if (pt_strTriangle->tb_Angle[0]) {
			//-- conversion de alpha -> ° -> radian 
			Conversion_DegRad(pt_strTriangle);	//-- conversion Degré - Radian 

			//-- test si sgement hypothénuse entré 
			if (pt_strTriangle->triangle_s.hypotenuse) {
				//Calcul -> cos(alpha) = adj / hyp => ... 
				pt_strTriangle->triangle_s.adjacent = cos(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.hypotenuse;

				//Calcul -> sin(alpha) = opp / hyp => ...
				pt_strTriangle->triangle_s.oppose = sin(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.hypotenuse;
			}
			//-- test si sgement adjacent entré 
			else if (pt_strTriangle->triangle_s.adjacent) {
				//Calcul -> cos(alpha) = adj/hyp => ...
				pt_strTriangle->triangle_s.hypotenuse = pt_strTriangle->triangle_s.adjacent / cos(pt_strTriangle->tb_Angle[1]);

				//Calcul -> tan(alpha) = opp/adj => ...
				pt_strTriangle->triangle_s.oppose = tan(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.adjacent;
			}
			//-- test si sgement opposé entré  
			else if (pt_strTriangle->triangle_s.oppose) {
				//Calcul -> sin(alpha) = opp/hyp => ...
				pt_strTriangle->triangle_s.hypotenuse = pt_strTriangle->triangle_s.oppose / sin(pt_strTriangle->tb_Angle[1]);

				//Calcul -> tan(alpha) = opp/adj => ...
				pt_strTriangle->triangle_s.adjacent = pt_strTriangle->triangle_s.oppose / tan(pt_strTriangle->tb_Angle[1]);
			}
		}

	}
	

	//-- check si la longeur des segments bien calculé 
	if(pt_strTriangle->triangle_s.hypotenuse && pt_strTriangle->triangle_s.oppose && pt_strTriangle->triangle_s.adjacent)
	checkFct = ok;

	//-- retourne OK
	return checkFct;
}
