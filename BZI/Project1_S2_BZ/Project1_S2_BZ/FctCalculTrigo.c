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
#include <stdio.h>
#include <math.h>
//--- librairie perso ---//
#include"CalculTrigo.h"

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: InitialiserStructure 
// -> PARAMETRES ENTRES			: 
// -> PARAMETRE SORTIE			: e_validation 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle 
// -> description				: tous les champs de la structure seront mis à zéro
 ----------------------------------------------------------------------------------*/
e_validation InitialisationStructure(str_triangleRectangle* pt_strTriangle) {
	//-- déclaration variables --// 
	
	
	//-- pirmaire --// 
	int i;
	//-- enumeration --// 
	e_validation checkFct = 0;
	
	//-- boucle pour initilaiser le tableau des angles --//
	for ( i = 0; i < 4; i++) {
		pt_strTriangle->tb_Angle[i]=0; 
	}

	//-- initialisation des cotés -> adj - hyp - opp --// 
	pt_strTriangle->triangle_s.adjacent = 0; // pointeur de strucure
	pt_strTriangle->triangle_s.hypotenuse = 0; // pointeur de strucure
	pt_strTriangle->triangle_s.oppose = 0; // pointeur de strucure
	//-- initialisation des champs de air et perimètres --// 
	pt_strTriangle->air = 0;
	pt_strTriangle->perimetre = 0;
	//-- validation -> de la fct --// 
	checkFct = ok;

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

	
void Conversion_DegRad(str_triangleRectangle* pt_strTriangle) {
	//-- test si angle à convertir --//          
	if (pt_strTriangle->tb_Angle[0] != 0) {
		//--> alpha 
		pt_strTriangle->tb_Angle[1] = (float)(M_PI / 180) * pt_strTriangle->tb_Angle[0];
	}
	if (pt_strTriangle->tb_Angle[2] != 0) {
		//--> beta 
		pt_strTriangle->tb_Angle[3] = (float)(M_PI / 180) * pt_strTriangle->tb_Angle[2];
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
void Conversion_RadDeg(str_triangleRectangle* pt_strTriangle) {

	//-- test si angle à convertir --//
	if (pt_strTriangle->tb_Angle[1] != 0) {
		//--> alpha 
		pt_strTriangle->tb_Angle[0] = (float)(180/M_PI) * pt_strTriangle->tb_Angle[1];
	}
	if (pt_strTriangle->tb_Angle[3] != 0) {
		//--> beta 
		pt_strTriangle->tb_Angle[2] = (float)(180 / M_PI) * pt_strTriangle->tb_Angle[3];
	}
}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculAllAngles
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: si angle rentré alors alors détermine le 2ème angle 
 ----------------------------------------------------------------------------------*/


e_validation CalculeAllAngles(str_triangleRectangle* pt_strTriangle) {

	e_validation checkFct = nok;




	//-- si pas d'angle défini 
	if ((pt_strTriangle->tb_Angle[0] == 0) &&
		(pt_strTriangle->tb_Angle[1] == 0) &&
		(pt_strTriangle->tb_Angle[2] == 0) &&
		(pt_strTriangle->tb_Angle[3] == 0))
	{
		//-- si coté non défini -> hypothénuse -> fonction trigo inversée arctan 
		if (pt_strTriangle->triangle_s.hypotenuse == 0) {
			pt_strTriangle->tb_Angle[1] = (float)(atan((double)(pt_strTriangle->triangle_s.oppose / (double)pt_strTriangle->triangle_s.adjacent)));


			//-- conversion Radian - Degré 
			Conversion_RadDeg(pt_strTriangle);

		}
		//-- si coté non défini -> opposé -> fonction trigo inversée arccos
		else if (pt_strTriangle->triangle_s.oppose == 0) {
			pt_strTriangle->tb_Angle[1] = (float)(acos((double)pt_strTriangle->triangle_s.adjacent / (double)pt_strTriangle->triangle_s.hypotenuse));


			//-- conversion Radian - Degré 
			Conversion_RadDeg(pt_strTriangle);
		}
		//-- si coté non défini -> adjacent -> fonction trigo inversée arcsin
		else if (pt_strTriangle->triangle_s.adjacent == 0) {
			pt_strTriangle->tb_Angle[1] = (float)(asin((double)pt_strTriangle->triangle_s.oppose / (double)pt_strTriangle->triangle_s.hypotenuse));

			//-- conversion Radian - Degré 
			Conversion_RadDeg(pt_strTriangle);
		}
		//-- test si tous les champs sont remplis 
		//-- test si un angle a été définit alpha ou beta 


	}

	else if (pt_strTriangle->tb_Angle[2] != 0)
		{
			//-- calcul de alpha 
			pt_strTriangle->tb_Angle[0] = 90 - pt_strTriangle->tb_Angle[2];
			//-- conversion Degré - Radian 
			Conversion_DegRad(pt_strTriangle);
		}
	else if ((pt_strTriangle->tb_Angle[0] != 0))
		{
			//-- calcul de beta
			pt_strTriangle->tb_Angle[2] = 90 - pt_strTriangle->tb_Angle[0];
			//-- conversion Degré - Radian 
			Conversion_DegRad(pt_strTriangle);
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
e_validation CalculeLongeurSegment(str_triangleRectangle* pt_strTriangle) {
	
	e_validation checkFct=0;
	
	
	//-- test -> si pas aucun angle définit 
	if ((pt_strTriangle->tb_Angle[0] == 0) &&
		(pt_strTriangle->tb_Angle[1] == 0) &&
		(pt_strTriangle->tb_Angle[2] == 0) &&
		(pt_strTriangle->tb_Angle[3] == 0))
	{
		CalculeAllAngles(pt_strTriangle);
		//-- test si la valeur à calculer est à zéro 
		if (pt_strTriangle->triangle_s.adjacent == 0) {
			//CalculeAllAngles(pt_strTriangle);
			//-- calculer segment adjacent --//
			pt_strTriangle->triangle_s.adjacent = sqrt(pow((double)pt_strTriangle->triangle_s.hypotenuse, 2) - (pow((double)pt_strTriangle->triangle_s.oppose, 2)));
		}
		//-- calculer segment hypothénuse --// 
		else if (pt_strTriangle->triangle_s.hypotenuse == 0) {
			//CalculeAllAngles(pt_strTriangle);
			//-- calculer segment adjacent --//
			pt_strTriangle->triangle_s.hypotenuse = sqrt(pow((double)pt_strTriangle->triangle_s.adjacent, 2) + (pow((double)pt_strTriangle->triangle_s.oppose, 2)));
		}
		//-- calculer segment opposé 
		else if (pt_strTriangle->triangle_s.oppose == 0) {
			//CalculeAllAngles(pt_strTriangle);
			//-- calculer segment adjacent --//
			pt_strTriangle->triangle_s.oppose = sqrt(pow((double)pt_strTriangle->triangle_s.hypotenuse, 2) - (pow((double)pt_strTriangle->triangle_s.adjacent, 2)));
		}
		
	} 

	
		//-- test si un angle a été définit alpha ou beta 
	else if ((pt_strTriangle->tb_Angle[0] != 0) || (pt_strTriangle->tb_Angle[2] != 0))
	{
		
		//-- test si l'angle alpha a été inséré 
		if (pt_strTriangle->tb_Angle[0] != 0) {
			//-- conversion de alpha -> ° -> radian 
			Conversion_DegRad(pt_strTriangle);

			//-- test si sgement hypothénuse entré 
			if (pt_strTriangle->triangle_s.hypotenuse != 0) {


				//Calcul -> cos(alpha) = adj / hyp => ... 
				pt_strTriangle->triangle_s.adjacent = cos(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.hypotenuse;

				//Calcul -> sin(alpha) = opp / hyp => ...
				pt_strTriangle->triangle_s.oppose = sin(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.hypotenuse;


			}
			//-- test si sgement adjacent entré 
			else if (pt_strTriangle->triangle_s.adjacent != 0) {
				//Calcul -> cos(alpha) = adj/hyp => ...
				pt_strTriangle->triangle_s.hypotenuse = pt_strTriangle->triangle_s.adjacent / cos(pt_strTriangle->tb_Angle[1]);
				//Calcul -> tan(alpha) = opp/adj => ...
				pt_strTriangle->triangle_s.oppose = pt_strTriangle->triangle_s.adjacent * tan(pt_strTriangle->tb_Angle[1]);


			}
			//-- test si sgement opposé entré  
			else if (pt_strTriangle->triangle_s.oppose != 0) {
				//Calcul -> sin(alpha) = opp/hyp => ...
				pt_strTriangle->triangle_s.hypotenuse = pt_strTriangle->triangle_s.oppose / sin(pt_strTriangle->tb_Angle[1]);

				//Calcul -> tan(alpha) = opp/adj => ... 
				pt_strTriangle->triangle_s.adjacent = pt_strTriangle->triangle_s.oppose / tan(pt_strTriangle->tb_Angle[1]);
			}
			
			
		}
		
		//-- calcul de tous les angles -> appel de fct --// 

	}	CalculeAllAngles(pt_strTriangle);

//-- check si la longeur des segments bien calculé 
	return checkFct;

}











