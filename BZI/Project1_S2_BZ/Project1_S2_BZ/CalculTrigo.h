//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet 2 - Calculs Trigo
// Nom du fichier 		: CalculsTrigo.h
// Date de création 	: 14.02.2024
// Date de modification : 14.02.2024
//
// Auteur 				: Philou (Ph. Bovey)
//
// Description          : 
//
// Remarques			: voir donnee de l'épreuve            
//----------------------------------------------------------------------------------//
#ifndef CALCUL_TRIGO_H
#define CALCUL_TRIGO_H

//-- déclaration -> définition globales --// 
#define NB_CHOIX_MAX 2


//-- déclaration -> énumération globales --// 
typedef enum { cote, angle } e_choixCoteAngle;
typedef enum { adj = 1, hyp, opp } e_choixCote;
typedef enum { alpha = 1, beta } e_choixAngle;
typedef enum { ok, nok} e_validation;


//-- déclaration -> structure globales --//
//--> structure 1
typedef struct  {
	unsigned char adjacent;
	unsigned char hypotenuse;
	unsigned char oppose;
}str_coteTriangle;
//--> structure 2
typedef struct  {
	float tb_Angle[4]; 
	str_coteTriangle triangle_s;
	struct Str_AetP {
		short air;
		char perimetre;
	};
}str_triangleRectangle;

//-- déclaration de prototype --// 
	//-> tous les champs de la structure seront mis à zéro
e_validation InitialisationStructure(str_triangleRectangle* pt_strTriangle);
	//-> conversion angle degré -> en radian 
void Conversion_DegRad(str_triangleRectangle *pt_strTriangle);
	//-> conversion angle radian -> en degré 
void Conversion_RadDeg(str_triangleRectangle* pt_strTriangle);
	//-> calculer les différents segments du triangle
e_validation CalculeAllAngles (str_triangleRectangle* pt_strTriangle);
	//-> calculer les différents angles 
e_validation CalculeLongeurSegment(str_triangleRectangle* pt_strTriangle);
#endif // !CALCUL_TRIGO_H