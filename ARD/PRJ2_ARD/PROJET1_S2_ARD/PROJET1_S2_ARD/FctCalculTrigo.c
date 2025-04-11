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
#include <math.h>
#include <stdio.h>


//--- librairie perso ---//
#include "CalculTrigo.h"

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: InitialiserStructure 
// -> PARAMETRES ENTRES			: 
// -> PARAMETRE SORTIE			: e_validation 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle 
// -> description				: tous les champs de la structure seront mis à zéro
 ----------------------------------------------------------------------------------*/
e_validation Initialiserstructure(str_triangleRectangle* pointeur_strTriangle) {
	//-- déclaration variables --// 
	int compteur = 0;
	//-- pirmaire --// 
	//-- enumeration --//
	e_validation controleFonction = 0; 
	//-- boucle pour initilaiser le tableau des angles --//
	for (compteur = 0; compteur < 4; compteur++) {
		pointeur_strTriangle->tb_Angle[compteur] = 0; //les valeur 0 et 2 sont en degré et 1 et 3 en radiant
	}

	//-- initialisation des cotés -> adj - hyp - opp --// 
	pointeur_strTriangle->triangle_s.adjacent = 0; // pointeur pour l'adjacent dans la structure
	pointeur_strTriangle->triangle_s.hypotenuse = 0; // pointeur pour l'hypotenuse dans la structure
	pointeur_strTriangle->triangle_s.oppose = 0; // pointeur pour l'oppose dans la structure
	//-- initialisation des champs de air et perimètres --// 
	pointeur_strTriangle->air = 0; // pointeur pour l'air dans la structure
	pointeur_strTriangle->perimetre = 0; // pointeur pour le perimetre dans la structure
	//-- validation -> de la fct --// 

	//-- valeur à retourner --// 
	return controleFonction;
}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_DegRad
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en degré -> déterminer sa valeur 
//								  en radian 
 ----------------------------------------------------------------------------------*/
void Conversion_DegRad(str_triangleRectangle* pointeur_strTriangle){
	//-- test si angle à convertir --//
	//--> alpha 
	if (pointeur_strTriangle->tb_Angle[0] > 0){//verifie que c'est pas à 0 degré
		pointeur_strTriangle->tb_Angle[1] = (float)(M_PI / 180) * pointeur_strTriangle->tb_Angle[0]; //transforme en radian
	}
	//--> beta 
	if (pointeur_strTriangle->tb_Angle[2] > 0) {//verifie que c'est pas à 0 degré
		pointeur_strTriangle->tb_Angle[3] = (float)(M_PI / 180) * pointeur_strTriangle->tb_Angle[2]; //transforme en radian
	}
}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_RadDeg
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			:
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en radian -> déterminer sa valeur
//								  en degré
 ----------------------------------------------------------------------------------*/
void Conversion_RadDeg(str_triangleRectangle* pointeur_strTriangle){
	//-- test si angle à convertir --//
	//--> alpha 
	if (pointeur_strTriangle->tb_Angle[1] > 0) {//verifie que c'est pas à 0 radian
		pointeur_strTriangle->tb_Angle[0] = (float)(180 / M_PI) * pointeur_strTriangle->tb_Angle[1]; //transforme en degré
	}
	//--> beta 
	if (pointeur_strTriangle->tb_Angle[3] > 0) {//verifie que c'est pas à 0 radian
		pointeur_strTriangle->tb_Angle[2] = (float)(180 / M_PI) * pointeur_strTriangle->tb_Angle[3]; //transforme en degré
	}
}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculAllAngles
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: si angle rentré alors alors détermine le 2ème angle 
 ----------------------------------------------------------------------------------*/
e_validation CalculerAllAngles(str_triangleRectangle* pointeur_strTriangle){
	e_validation controleFonction = nok;
	if (pointeur_strTriangle->tb_Angle[2] != 0)
	{
		pointeur_strTriangle->tb_Angle[0] = 90 - pointeur_strTriangle->tb_Angle[2];
		Conversion_DegRad(pointeur_strTriangle);
	}
	if (pointeur_strTriangle->tb_Angle[0] != 0)
	{
		pointeur_strTriangle->tb_Angle[2] = 90 - pointeur_strTriangle->tb_Angle[0];
		Conversion_DegRad(pointeur_strTriangle);
	}

	//-- test si un angle a été définit alpha ou beta 
	//-- si pas d'angle défini 
	if ((pointeur_strTriangle->tb_Angle[0] == 0) || (pointeur_strTriangle->tb_Angle[1] == 0) || (pointeur_strTriangle->tb_Angle[2] == 0) ||	(pointeur_strTriangle->tb_Angle[3] == 0))
	{
		//-- si coté non défini -> hypothénuse -> fonction trigo inversée arctan 
		if (pointeur_strTriangle->triangle_s.hypotenuse == 0) { 
			pointeur_strTriangle->tb_Angle[1] = (atan(((float)pointeur_strTriangle->triangle_s.oppose / (float)pointeur_strTriangle->triangle_s.adjacent)));
			//-- conversion Radian - Degré
			Conversion_RadDeg(pointeur_strTriangle);
		}
			 
		

		//-- si coté non défini -> opposé -> fonction trigo inversée arccos
		else if (pointeur_strTriangle->triangle_s.oppose == 0) {
			pointeur_strTriangle->tb_Angle[1] = (acos(((float)pointeur_strTriangle->triangle_s.adjacent / (float)pointeur_strTriangle->triangle_s.hypotenuse)));
			//-- conversion Radian - Degré 
			Conversion_RadDeg(pointeur_strTriangle);
		} 
		
		
		//-- si coté non défini -> adjacent -> fonction trigo inversée arcsin
		else if (pointeur_strTriangle->triangle_s.adjacent == 0) {
				pointeur_strTriangle->tb_Angle[1] = (asin(((float)pointeur_strTriangle->triangle_s.oppose / (float)pointeur_strTriangle->triangle_s.hypotenuse)));
				//-- conversion Radian - Degré
				Conversion_RadDeg(pointeur_strTriangle);
		}
	}

			
			
			return controleFonction;
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
e_validation CalculerLongueurSegment(str_triangleRectangle * pointeur_strTriangle) {
	e_validation controleFonction = 0;
	//-- test -> si pas aucun angle définit 
	if ((pointeur_strTriangle->tb_Angle[0] == 0) && (pointeur_strTriangle->tb_Angle[1] == 0) && (pointeur_strTriangle->tb_Angle[2] == 0) && (pointeur_strTriangle->tb_Angle[3] == 0))
	{
		CalculerAllAngles(pointeur_strTriangle);
		//-- test si la valeur à calculer est à zéro 
		if (pointeur_strTriangle->triangle_s.adjacent == 0) {
			//-- calculer segment adjacent --//
			pointeur_strTriangle->triangle_s.adjacent = (sqrt(pow((float)pointeur_strTriangle->triangle_s.hypotenuse, 2) - (pow((float)pointeur_strTriangle->triangle_s.oppose, 2))));
		}
		//-- test si la valeur à calculer est à zéro
		else if (pointeur_strTriangle->triangle_s.hypotenuse == 0) {
			//-- calculer segment hypothénuse --//
			pointeur_strTriangle->triangle_s.hypotenuse = (sqrt(pow((float)pointeur_strTriangle->triangle_s.adjacent, 2) + (pow((float)pointeur_strTriangle->triangle_s.oppose, 2))));
		}
		//-- test si la valeur à calculer est à zéro
		else if (pointeur_strTriangle->triangle_s.oppose == 0) {
			//-- calculer segment opposé 
			pointeur_strTriangle->triangle_s.oppose = (sqrt(pow((float)pointeur_strTriangle->triangle_s.hypotenuse, 2) - (pow((float)pointeur_strTriangle->triangle_s.adjacent, 2))));
		}
	}
		//-- test si un angle a été définit alpha ou beta 
	if ((pointeur_strTriangle->tb_Angle[0] > 0) || (pointeur_strTriangle->tb_Angle[2] > 0))
	{
		//-- test si l'angle alpha a été inséré 
		if (pointeur_strTriangle->tb_Angle[0] > 0) 
		{
			//-- conversion de alpha -> ° -> radian 
			Conversion_DegRad(pointeur_strTriangle);

			//-- test si sgement hypothénuse entré 
			if (pointeur_strTriangle->triangle_s.hypotenuse > 0) 
			{
				//Calcul -> cos(alpha) = adj / hyp => ... 
				pointeur_strTriangle->triangle_s.adjacent = (cos((float)pointeur_strTriangle->tb_Angle[1]) * (float)pointeur_strTriangle->triangle_s.hypotenuse);

				//Calcul -> sin(alpha) = opp / hyp => ...
				pointeur_strTriangle->triangle_s.oppose = (sin((float)pointeur_strTriangle->tb_Angle[1]) * (float)pointeur_strTriangle->triangle_s.hypotenuse);
			}
			//-- test si sgement adjacent entré 
			else if (pointeur_strTriangle->triangle_s.adjacent > 0) 
			{
				//Calcul -> cos(alpha) = adj/hyp => ...
				pointeur_strTriangle->triangle_s.hypotenuse = pointeur_strTriangle->triangle_s.adjacent / (cos((float)pointeur_strTriangle->tb_Angle[1]));

				//Calcul -> tan(alpha) = opp/adj => ...
				pointeur_strTriangle->triangle_s.oppose = pointeur_strTriangle->triangle_s.adjacent * (tan((float)pointeur_strTriangle->tb_Angle[1]));

			}
			//-- test si sgement opposé entré  
			else if (pointeur_strTriangle->triangle_s.oppose > 0) 
			{
				//Calcul -> sin(alpha) = opp/hyp => ...
				pointeur_strTriangle->triangle_s.hypotenuse = pointeur_strTriangle->triangle_s.oppose / (sin((float)pointeur_strTriangle->tb_Angle[1]));

				//Calcul -> tan(alpha) = opp/adj => ... 
				pointeur_strTriangle->triangle_s.adjacent = pointeur_strTriangle->triangle_s.oppose / (tan((float)pointeur_strTriangle->tb_Angle[1]));
			}
		}		

	}
	//-- calcul de tous les angles -> appel de fct --// 
	CalculerAllAngles(pointeur_strTriangle);

	//-- check si la longeur des segments bien calculé 
	return controleFonction;

}