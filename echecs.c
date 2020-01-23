#include "echecs.h"

int main(){
	plateau p;
	initp(&p);
	newp(&p);
/*
	p.grille[0][0] = -1;
	p.grille[0][1] = -1;
	p.grille[0][2] = -1;
	p.grille[0][3] = -1;
	p.grille[0][4] = -1;
	p.grille[0][5] = -1;
	p.grille[0][6] = 0;
	p.grille[0][7] = -1;
	p.grille[1][0] = 11;
	p.grille[1][1] = 8;
	p.grille[1][2] = -1;
	p.grille[1][3] = -1;
	p.grille[1][4] = 4;
	p.grille[1][5] = -1;
	p.grille[1][6] = 10;
	p.grille[1][7] = 2;
	p.grille[2][0] = 11;
	p.grille[2][1] = -1;
	p.grille[2][2] = -1;
	p.grille[2][3] = -1;
	p.grille[2][4] = -1;
	p.grille[2][5] = -1;
	p.grille[2][6] = -1;
	p.grille[2][7] = -1;
	p.grille[3][0] = 5;
	p.grille[3][1] = -1;
	p.grille[3][2] = -1;
	p.grille[3][3] = 1;
	p.grille[3][4] = -1;
	p.grille[3][5] = -1;
	p.grille[3][6] = -1;
	p.grille[3][7] = 5;
	p.grille[4][0] = 8;
	p.grille[4][1] = -1;
	p.grille[4][2] = -1;
	p.grille[4][3] = 9;
	p.grille[4][4] = -1;
	p.grille[4][5] = -1;
	p.grille[4][6] = -1;
	p.grille[4][7] = -1;
	p.grille[5][0] = -1;
	p.grille[5][1] = 10;
	p.grille[5][2] = -1;
	p.grille[5][3] = -1;
	p.grille[5][4] = 11;
	p.grille[5][5] = -1;
	p.grille[5][6] = -1;
	p.grille[5][7] = -1;
	p.grille[6][0] = 6;
	p.grille[6][1] = 6;
	p.grille[6][2] = -1;
	p.grille[6][3] = -1;
	p.grille[6][4] = -1;
	p.grille[6][5] = -1;
	p.grille[6][6] = -1;
	p.grille[6][7] = 11;
	p.grille[7][0] = -1;
	p.grille[7][1] = -1;
	p.grille[7][2] = 4;
	p.grille[7][3] = 7;
	p.grille[7][4] = -1;
	p.grille[7][5] = -1;
	p.grille[7][6] = 7;
	p.grille[7][7] = 3;
*/
	affp(p);
	selecp(p);
	return 0;
}

void selecp(plateau p){
	char c;
	printf("Qui doit jouer ?  (0 pour blanc / 1 pour noir)\n");
	scanf("%c",&c);
	viderBuffer();
	while(c != '0' && c != '1'){
		printf("Réponse invalide (0/1)\n");
		scanf("%c",&c);
		viderBuffer();
	}
	c -= '0';

	char nbc;
	printf("Echec et mat en combien de coups ?\n");
	scanf("%c",&nbc);
	viderBuffer();
	while(nbc < '1'){
		printf("Réponse invalide\n");
		scanf("%c",&nbc);
		viderBuffer();
	}
	nbc -= '0';

	solution s = resop(p, 1, nbc*2 -1, c);

	if(s.sol){
		printf("\n");
		affp(p);
		afficherarbre(s.hist, 1);
	}
	else
		printf("Pas de solution...\n");
}

solution resop(plateau p, int coup, int nbc , int c){
	int lscoup[27];
	int i,j;
	int k;
	plateau p2;
	int z = 1;

	solution solutionact;
	solutionact.hist = initarbre();

	solution solutionsuiv;
	solutionsuiv.hist = initarbre();

	int nc = 0;
	if (coup == 1){
		for(i=0 ; i<8 ; i++){
			for(j=0; j<8 ; j++){
				if(p.grille[i][j] != -1 && p.grille[i][j]%2 == c){
					initlscoup(lscoup);
					coupslegaux(p, i*10 + j, lscoup, 1);
					for(k=0 ; lscoup[k] != -1 ; k++)
						nc++;
				}
			}
		}
	}
	p2 = p;
	if(coup%2 == 1){
		solutionact.sol = 0;
		if(coup <= nbc){
			for(i=0 ; i<8 ; i++){
				for(j=0 ; j<8 ; j++){
					if(p.grille[i][j] != -1 && p.grille[i][j]%2 == c){
						initlscoup(lscoup);
						coupslegaux(p2, i*10 + j, lscoup, 1);
						for(k=0 ; lscoup[k] != -1 ; k++){
							deplp(&p2, i*10 + j, lscoup[k]);
							if(echec(p2,c ? 0:1)){
								if(mat(p2,c ? 0:1)){
									solutionact.sol = 1;
									inserefeuille(solutionact.hist, i*10 + j, lscoup[k]);
									return solutionact; //Mettre en commentaire cette ligne pour obtenir toutes les solutions et pas seulement la 1ere trouvée
								}
							}
							solutionsuiv = resop(p2, coup + 1, nbc, c ? 0:1);
							if(solutionsuiv.sol){
								inserearbre(solutionact.hist, solutionsuiv.hist, i*10 + j, lscoup[k]);
								solutionact.sol = 1;
							}
							p2 = p;
							if(coup == 1){
								printf("Recherche en cours : %d%c de scénarios testés\n", z++*100/nc, '%');
							}
						}
					}
				}
			}
			return solutionact;
		}
		solutionact.sol = 0;
	}
	else{
		if(coup <= nbc){
			solutionact.sol = 1;
			for(i=0 ; i<8 ; i++){
				for(j=0 ; j<8 ; j++){
					if(p.grille[i][j] != -1 && p.grille[i][j]%2 == c){
						initlscoup(lscoup);
						coupslegaux(p2, i*10 + j, lscoup, 1);
						for(k=0 ; lscoup[k] != -1 ; k++){
							deplp(&p2, i*10 + j, lscoup[k]);
							solutionsuiv = resop(p2, coup + 1, nbc, c ? 0:1);
							solutionact.sol *= solutionsuiv.sol;
							if(solutionsuiv.sol)
								inserearbre(solutionact.hist, solutionsuiv.hist, i*10 + j, lscoup[k]);
							p2 = p;
						}
					}
				}
			}
			if(!solutionact.sol)
				free(solutionact.hist);
			return solutionact;
		}
		solutionact.sol = 0;
	}
	return solutionact;
}

void initp(plateau *p){
	int i,j;
	for(i=0 ; i<8 ; i++){
		for(j=0 ; j<8 ; j++){
			p->grille[i][j] = -1;
		}
	}
	for(i=0 ; i<13 ; i++){
		p->Nbp[i] = 0;
	}
	decomptepieces(p);
}

void newp(plateau *p){
	int r = 1;
	char r1;
	char r2;
	char coord[2];
	char type[2];
	int o,a; //Ordonnée et abscisse
	int t; //Type de pièce
	while(r){
		affp(*p);
		printf("Voulez-vous placez une nouvelle pièce ? (o/n)\n");
		scanf("%c",&r1);
		viderBuffer();
		while(r1 != 'o' && r1 != 'n'){
			printf("Réponse invalide (o/n)\n");
			scanf("%c",&r1);
			viderBuffer();
		}
		if (r1 == 'o'){
			printf("Ou voulez-vous placez votre pièce ? (Exemple : A1)\n");
			scanf("%s",coord);
			viderBuffer();
			while(coord[0] < 'A' || coord[0] > 'H' || coord[1] < '1' || coord[1] > '8'){
				if (coord[0] >= 'a' && coord[0] <= 'h'){
					coord[0] += 'A' - 'a';
					break;
				}
				printf("Les coordonnées que vous avez entré sont incorrectes. Ex:[A à H][1 à 8]\nVeuillez saisir de nouvelles coordonées\n");
				scanf("%s",coord);
				viderBuffer();
			}
			a = coord[0] - 'A';
			o = (coord[1] - '8') * -1;
			if (p->grille[o][a] != -1){
				printf("Il y a déjà une pièce sur cette case voulez-vous la remplacer ? (o/n)\n");
				scanf("%c",&r2);
				viderBuffer();
				while(r2 != 'o' && r2 != 'n'){
					printf("Réponse invalide (o/n)\n");
					scanf("%c",&r2);
					viderBuffer();
				}
				if(r2 == 'n'){
					continue;
				}
				p->grille[o][a] = -1;
				decomptepieces(p);
			}
			printf("Quel type de pièce ? (Rn / Rb / Dn / Db / Tn / Tb / Fn / Fb / Cn / Cb / Pn / Pb)\n");
			scanf("%s",type);
			viderBuffer();
			while(type[0] != 'R' && type[0] != 'D' && type[0] != 'T' && type[0] != 'F' && type[0] != 'C' && type[0] != 'P'){
				if(type[0] == 'r' || type[0] == 'd' || type[0] == 't' || type[0] == 'f' || type[0] == 'c' || type[0] == 'p'){
					type[0] += 'A' - 'a';
					break;
				}
				printf("Le type de pièce que vous avez entré est incorrect.\nEx:(Rn / Rb / Dn / Db / Tn / Tb / Fn / Fb / Cn / Cb / Pn / Pb)\nVeuillez saisir à nouveau le type de pièce\n");
				scanf("%s",type);
				viderBuffer();
			}
			while(type[1] != 'n' && type[1] != 'b'){
				printf("La couleur de la pièce est incorrecte. (n pour noir / b pour blanc)\nVeuillez saisir une nouvelle couleur\n");
				char bn;
				scanf("%c",&bn);
				viderBuffer();
				type[1] = bn;
			}
			t = convert(type);


			if (tropdepieces(*p,t)){
				printf("Il y a trop de pièces de ce type !!!\n\n");
				continue;
			}

			if (t == 10 || t == 11){
				if(o == 0 || o == 7){
					printf("Il ne peut pas y avoir de pion ici !!!\n\n");
					continue;
				}
			}
			if (t == 0){
				if(	(p->grille[o - 1][a] 	== 1	&& coordvalide((o * 10 + a) - 10))	||
					(p->grille[o - 1][a - 1] == 1	&& coordvalide((o * 10 + a) - 11))	||
					(p->grille[o - 1][a + 1] == 1	&& coordvalide((o * 10 + a) - 9))	||
					(p->grille[o][a - 1] 	== 1	&& coordvalide((o * 10 + a) - 1))	||
					(p->grille[o][a + 1] 	== 1	&& coordvalide((o * 10 + a) + 1))	||
					(p->grille[o + 1][a - 1] == 1	&& coordvalide((o * 10 + a) + 9)) 	||
					(p->grille[o + 1][a + 1] == 1	&& coordvalide((o * 10 + a) + 11))	||
					(p->grille[o + 1][a] 	== 1	&& coordvalide((o * 10 + a) + 10))) {

					printf("Il ne peut pas y avoir de roi blanc ici !!!\n\n");
					continue;
				}
			}
			if (t == 1){
				if(	(p->grille[o - 1][a] 	== 0	&& coordvalide((o * 10 + a) - 10))	||
					(p->grille[o - 1][a - 1] == 0	&& coordvalide((o * 10 + a) - 11))	||
					(p->grille[o - 1][a + 1] == 0	&& coordvalide((o * 10 + a) - 9))	||
					(p->grille[o][a - 1] 	== 0	&& coordvalide((o * 10 + a) - 1))	||
					(p->grille[o][a + 1] 	== 0	&& coordvalide((o * 10 + a) + 1))	||
					(p->grille[o + 1][a - 1] == 0	&& coordvalide((o * 10 + a) + 9))	||
					(p->grille[o + 1][a + 1] == 0	&& coordvalide((o * 10 + a) + 11))	||
					(p->grille[o + 1][a] 	== 0	&& coordvalide((o * 10 + a) + 10)))	{

					printf("Il ne peut pas y avoir de roi noir ici !!!\n\n");
					continue;
				}
			}

			p->grille[o][a] = t;
			decomptepieces(p);
		}
		else{
			if(p->Nbp[0] == 0 || p->Nbp[1] == 0){
				printf("Il manque au moins un roi sur l'échiquier !!!\n\n");
				continue;
			}
			r = 0;
		}
	}
}

int tropdepieces(plateau p, int t){
	int promotion = 0, i;
	for(i=2 ; i<10 ; i++){
		if(i == 2 || i == 3){
			if(p.Nbp[i]>1)
				promotion += p.Nbp[i] - 1;
		}
		else if(p.Nbp[i]>2)
			promotion += p.Nbp[i] - 2;
	}
	switch (t){
		case 0:
		if(p.Nbp[0] == 1)
			return 1;
		break;

		case 1:
		if(p.Nbp[1] == 1)
			return 1;
		break;

		case 2:
		if(p.Nbp[2] > 1){
			if(1 + promotion + p.Nbp[10] == 9)
				return 1;
			break;
		}
		if(p.Nbp[2] + promotion + p.Nbp[10] == 9)
			return 1;
		break;

		case 3:
		if(p.Nbp[3] > 1){
			if(1 + promotion + p.Nbp[11] == 9)
				return 1;
			break;
		}
		if(p.Nbp[3] + promotion + p.Nbp[11] == 9)
			return 1;
		break;

		case 4:
		if(p.Nbp[4] > 2){
			if(2 + promotion + p.Nbp[10] == 10)
				return 1;
			break;
		}
		if(p.Nbp[4] + promotion + p.Nbp[10] == 10)
			return 1;
		break;

		case 5:
		if(p.Nbp[5] > 2){
			if(2 + promotion + p.Nbp[11] == 10)
				return 1;
			break;
		}
		if(p.Nbp[5] + promotion + p.Nbp[11] == 10)
			return 1;
		break;

		case 6:
		if(p.Nbp[6] > 2){
			if(2 + promotion + p.Nbp[10] == 10)
				return 1;
			break;
		}
		if(p.Nbp[6] + promotion + p.Nbp[10] == 10)
			return 1;
		break;

		case 7:
		if(p.Nbp[7] > 2){
			if(2 + promotion + p.Nbp[11] == 10)
				return 1;
			break;
		}
		if(p.Nbp[7] + promotion + p.Nbp[11] == 10)
			return 1;
		break;

		case 8:
		if(p.Nbp[8] > 2){
			if(2 + promotion + p.Nbp[10] == 10)
				return 1;
			break;
		}
		if(p.Nbp[8] + promotion + p.Nbp[10] == 10)
			return 1;
		break;

		case 9:
		if(p.Nbp[9] > 2){
			if(2 + promotion + p.Nbp[11] == 10)
				return 1;
			break;
		}
		if(p.Nbp[9] + promotion + p.Nbp[11] == 10)
			return 1;
		break;

		case 10:
		if(p.Nbp[10] + promotion == 8) 
			return 1;
		break;

		case 11:
		if(p.Nbp[11] + promotion == 8) 
			return 1;
		break;

		default:
		return 0;
	}
	return 0;
}

int convert(char * nom){
	switch (nom[0]){
		case 'R':
		if(nom[1]=='b')
			return 0;
		return 1;
		break;

		case 'D':
		if(nom[1]=='b')
			return 2;
		return 3;
		break;

		case 'T':
		if(nom[1]=='b')
			return 4;
		return 5;
		break;

		case 'F':
		if(nom[1]=='b')
			return 6;
		return 7;
		break;

		case 'C':
		if(nom[1]=='b')
			return 8;
		return 9;
		break;

		case 'P':
		if(nom[1]=='b')
			return 10;
		return 11;
		break;

		default:
		return -1;
	}
}

void affp(plateau p){
	int i,j;
	printf("  | A | B | C | D | E | F | G | H |\n— + — + — + — + — + — + — + — + — + —\n");
	for(i=0 ; i<8 ; i++){
		printf("%d |",8-i);
		for(j=0 ; j<8 ; j++)
			affc(p.grille[i][j]);
		printf(" %d",8-i);
		printf("\n— + — + — + — + — + — + — + — + — + —\n");
	}
	printf("  | A | B | C | D | E | F | G | H |\n\n");
}

void affc(int c){
	switch (c){
		case -1:
		printf("   |");
		break;

		case 0:
		printf(" R |");
		break;

		case 1:
		couleur("31");
		printf(" R ");
		couleur("0");
		printf("|");
		break;

		case 2:
		printf(" D |");
		break;

		case 3:
		couleur("31");
		printf(" D ");
		couleur("0");
		printf("|");
		break;
		
		case 4:
		printf(" T |");
		break;

		case 5:
		couleur("31");
		printf(" T ");
		couleur("0");
		printf("|");
		break;

		case 6:
		printf(" F |");
		break;

		case 7:
		couleur("31");
		printf(" F ");
		couleur("0");
		printf("|");
		break;

		case 8:
		printf(" C |");
		break;

		case 9:
		couleur("31");
		printf(" C ");
		couleur("0");
		printf("|");
		break;

		case 10:
		printf(" P |");
		break;

		case 11:
		couleur("31");
		printf(" P ");
		couleur("0");
		printf("|");
		break;

		default:
		printf("???|");
	}
}

void viderBuffer(){
    int c; 
    do { 
        c = getchar(); 
    } while (c != '\n' && c != EOF);
}

void decomptepieces(plateau *p){
	int i,j;
	for(i=0 ; i<12 ; i++)
		p->Nbp[i] = 0;
	
	for(i=0 ; i<8 ; i++){
		for(j=0 ; j<8 ; j++){
			if(p->grille[i][j] != -1)
				p->Nbp[p->grille[i][j]] += 1;
		}
	}
}

int coordvalide(int coord){
	int i;
	for(i=0 ; i<64 ; i++){
		if(	(coord >= 00 && coord <= 07) ||
			(coord >= 10 && coord <= 17) ||
			(coord >= 20 && coord <= 27) ||
			(coord >= 30 && coord <= 37) ||
			(coord >= 40 && coord <= 47) ||
			(coord >= 50 && coord <= 57) ||
			(coord >= 60 && coord <= 67) ||
			(coord >= 70 && coord <= 77))
			return 1;
	}
	return 0;
}

void deplp(plateau *p, int dep, int arr){
	p->grille[arr/10][arr%10]=p->grille[dep/10][dep%10];
	p->grille[dep/10][dep%10]= -1;

	if (p->grille[arr/10][arr%10] == 10 && arr/10 == 0){ //promotion pion blanc
		p->grille[arr/10][arr%10] = 2;
		decomptepieces(p);
	}

	else if (p->grille[arr/10][arr%10] == 11 && arr/10 == 7){ //promotion pion noir
		p->grille[arr/10][arr%10] = 3;
		decomptepieces(p);
	}
}

void coupslegaux(plateau p, int coord, int lscoup[27], int mode){
	int type;
	type = p.grille[coord/10][coord%10];
	int o = coord/10;
	int a = coord%10;
	int i;
	int c = 1;
	int d = 0;
	plateau p2;
	p2 = p;

	switch (type){
		case 0: //Roi Blanc
		c = 0;

		case 1: //Roi Noir
		if((p.grille[o - 1][a - 1])%2 != c && coordvalide(coord - 11)){
			deplp(&p2,coord,coord - 11);
			if(!echec(p2,c))
				ajoutercoup(lscoup, coord - 11);
			p2 = p;
		}

		if((p.grille[o - 1][a])%2 != c && coordvalide(coord - 10)){
			deplp(&p2,coord,coord - 10);
			if(!echec(p2,c))
				ajoutercoup(lscoup, coord - 10);
			p2 = p;
		}

		if((p.grille[o - 1][a + 1])%2 != c && coordvalide(coord - 9)){
			deplp(&p2,coord,coord - 9);
			if(!echec(p2,c))
				ajoutercoup(lscoup, coord - 9);
			p2 = p;
		}

		if((p.grille[o][a - 1])%2 != c && coordvalide(coord - 1)){
			deplp(&p2,coord,coord - 1);
			if(!echec(p2,c))
				ajoutercoup(lscoup, coord - 1);
			p2 = p;
		}

		if((p.grille[o][a + 1])%2 != c && coordvalide(coord + 1)){
			deplp(&p2,coord,coord + 1);
			if(!echec(p2,c))
				ajoutercoup(lscoup, coord + 1);
			p2 = p;
		}

		if((p.grille[o + 1][a - 1])%2 != c && coordvalide(coord + 9)){
			deplp(&p2,coord,coord + 9);
			if(!echec(p2,c))
				ajoutercoup(lscoup, coord + 9);
			p2 = p;
		}

		if((p.grille[o + 1][a])%2 != c && coordvalide(coord + 10)){
			deplp(&p2,coord,coord + 10);
			if(!echec(p2,c))
				ajoutercoup(lscoup, coord + 10);
			p2 = p;
		}

		if((p.grille[o + 1][a + 1])%2 != c && coordvalide(coord + 11)){
			deplp(&p2,coord,coord + 11);
			if(!echec(p2,c))
				ajoutercoup(lscoup, coord + 11);
			p2 = p;
		}
		break;

		case 2: //Dame Blanche
		d = 1;

		case 3: //Dame Noire
		for(i=1 ; (p.grille[o - i][a])%2 == -1 && coordvalide(coord - i*10) ; i++){
			if(mode){
				deplp(&p2, coord, coord - i*10);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*10);
		}
		if((p.grille[o - i][a])%2 == d && coordvalide(coord - i*10)){
			if(mode){
				deplp(&p2, coord, coord - i*10);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*10);
		}
		for(i=1 ; (p.grille[o - i][a - i])%2 == -1 && coordvalide(coord - i*11) ; i++){
			if(mode){
				deplp(&p2, coord, coord - i*11);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*11);
		}
		if((p.grille[o - i][a - i])%2 == d && coordvalide(coord - i*11)){
			if(mode){
				deplp(&p2, coord, coord - i*11);
				if(!echec(p2,d ? 0 : 1))	
					ajoutercoup(lscoup, coord - i*11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*11);
		}
		for(i=1 ; (p.grille[o - i][a + i])%2 == -1 && coordvalide(coord - i*9) ; i++){
			if(mode){
				deplp(&p2, coord, coord - i*9);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*9);
		}
		if((p.grille[o - i][a + i])%2 == d && coordvalide(coord - i*9)){
			if(mode){
				deplp(&p2, coord, coord - i*9);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*9);
		}

		for(i=1 ; (p.grille[o][a - i])%2 == -1 && coordvalide(coord - i) ; i++){
			if(mode){
				deplp(&p2, coord, coord - i);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i);
		}
		if((p.grille[o][a - i])%2 == d && coordvalide(coord - i)){
			if(mode){
				deplp(&p2, coord, coord - i);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i);
		}

		for(i=1 ; (p.grille[o][a + i])%2 == -1 && coordvalide(coord + i) ; i++){
			if(mode){
				deplp(&p2, coord, coord + i);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i);
		}
		if((p.grille[o][a + i])%2 == d && coordvalide(coord + i)){
			if(mode){
				deplp(&p2, coord, coord + i);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i);
		}

		for(i=1 ; (p.grille[o + i][a - i])%2 == -1 && coordvalide(coord + i*9) ; i++){
			if(mode){
				deplp(&p2, coord, coord + i*9);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*9);
		}
		if((p.grille[o + i][a - i])%2 == d && coordvalide(coord + i*9)){
			if(mode){
				deplp(&p2, coord, coord + i*9);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*9);
		}

		for(i=1 ; (p.grille[o + i][a + i])%2 == -1 && coordvalide(coord + i*11) ; i++){
			if(mode){
				deplp(&p2, coord, coord + i*11);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*11);
		}
		if((p.grille[o + i][a + i])%2 == d && coordvalide(coord + i*11)){
			if(mode){
				deplp(&p2, coord, coord + i*11);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*11);
		}

		for(i=1 ; (p.grille[o + i][a])%2 == -1 && coordvalide(coord + i*10) ; i++){
			if(mode){
				deplp(&p2, coord, coord + i*10);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*10);
		}
		if((p.grille[o + i][a])%2 == d && coordvalide(coord + i*10)){
			if(mode){
				deplp(&p2, coord, coord + i*10);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*10);
		}
		break;

		case 4: //Tour Blanche
		d = 1;

		case 5: //Tour Noire
		for(i=1 ; (p.grille[o - i][a])%2 == -1 && coordvalide(coord - i*10) ; i++){
			if(mode){
				deplp(&p2, coord, coord - i*10);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*10);
		}

		if((p.grille[o - i][a])%2 == d && coordvalide(coord - i*10)){
			if(mode){
				deplp(&p2, coord, coord - i*10);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*10);
		}

		for(i=1 ; (p.grille[o][a - i])%2 == -1 && coordvalide(coord - i) ; i++){
			if(mode){
				deplp(&p2, coord, coord - i);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i);
		}
		if((p.grille[o][a - i])%2 == d && coordvalide(coord - i)){
			if(mode){
				deplp(&p2, coord, coord - i);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i);
		}

		for(i=1 ; (p.grille[o][a + i])%2 == -1 && coordvalide(coord + i) ; i++){
			if(mode){
				deplp(&p2, coord, coord + i);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i);
		}
		if((p.grille[o][a + i])%2 == d && coordvalide(coord + i)){
			if(mode){
				deplp(&p2, coord, coord + i);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i);
		}

		for(i=1 ; (p.grille[o + i][a])%2 == -1 && coordvalide(coord + i*10) ; i++){
			if(mode){
				deplp(&p2, coord, coord + i*10);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*10);
		}
		if((p.grille[o + i][a])%2 == d && coordvalide(coord + i*10)){
			if(mode){
				deplp(&p2, coord, coord + i*10);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*10);
		}
		break;

		case 6: //Fou Blanc
		d = 1;

		case 7: //Fou Noir
		for(i=1 ; (p.grille[o - i][a - i])%2 == -1 && coordvalide(coord - i*11) ; i++){
			if(mode){
				deplp(&p2, coord, coord - i*11);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*11);
		}
		if((p.grille[o - i][a - i])%2 == d && coordvalide(coord - i*11)){
			if(mode){
				deplp(&p2, coord, coord - i*11);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*11);
		}

		for(i=1 ; (p.grille[o - i][a + i])%2 == -1 && coordvalide(coord - i*9) ; i++){
			if(mode){
				deplp(&p2, coord, coord - i*9);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*9);
		}
		if((p.grille[o - i][a + i])%2 == d && coordvalide(coord - i*9)){
			if(mode){
				deplp(&p2, coord, coord - i*9);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord - i*9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - i*9);
		}

		for(i=1 ; (p.grille[o + i][a - i])%2 == -1 && coordvalide(coord + i*9) ; i++){
			if(mode){
				deplp(&p2, coord, coord + i*9);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*9);
		}
		if((p.grille[o + i][a - i])%2 == d && coordvalide(coord + i*9)){
			if(mode){
				deplp(&p2, coord, coord + i*9);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*9);
		}

		for(i=1 ; (p.grille[o + i][a + i])%2 == -1 && coordvalide(coord + i*11) ; i++){
			if(mode){
				deplp(&p2, coord, coord + i*11);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*11);

		}
		if((p.grille[o + i][a + i])%2 == d && coordvalide(coord + i*11)){
			if(mode){
				deplp(&p2, coord, coord + i*11);
				if(!echec(p2,d ? 0 : 1))
					ajoutercoup(lscoup, coord + i*11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + i*11);
		}
		break;

		case 8: //Cavalier Blanc
		c = 0;

		case 9: //Cavalier Noir
		if((p.grille[o - 2][a - 1])%2 != c && coordvalide(coord - 21)){
			if(mode){
				deplp(&p2, coord, coord - 21);
				if(!echec(p2,c))
					ajoutercoup(lscoup, coord - 21);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - 21);
		}
		if((p.grille[o - 2][a + 1])%2 != c && coordvalide(coord - 19)){
			if(mode){
				deplp(&p2, coord, coord - 19);
				if(!echec(p2,c))
					ajoutercoup(lscoup, coord - 19);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - 19);
		}
		if((p.grille[o - 1][a - 2])%2 != c && coordvalide(coord - 12)){
			if(mode){
				deplp(&p2, coord, coord - 12);
				if(!echec(p2,c))
					ajoutercoup(lscoup, coord - 12);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - 12);
		}
		if((p.grille[o - 1][a + 1])%2 != c && coordvalide(coord - 8)){
			if(mode){
				deplp(&p2, coord, coord - 8);
				if(!echec(p2,c))
					ajoutercoup(lscoup, coord - 8);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - 8);
		}
		if((p.grille[o + 1][a - 2])%2 != c && coordvalide(coord + 8)){
			if(mode){
				deplp(&p2, coord, coord + 8);
				if(!echec(p2,c))
					ajoutercoup(lscoup, coord + 8);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + 8);
		}
		if((p.grille[o + 1][a + 2])%2 != c && coordvalide(coord + 12)){
			if(mode){
				deplp(&p2, coord, coord + 12);
				if(!echec(p2,c))
					ajoutercoup(lscoup, coord + 12);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + 12);
		}
		if((p.grille[o + 2][a - 1])%2 != c && coordvalide(coord + 19)){
			if(mode){
				deplp(&p2, coord, coord + 19);
				if(!echec(p2,c))
					ajoutercoup(lscoup, coord + 19);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + 19);
		}
		if((p.grille[o + 2][a + 1])%2 != c && coordvalide(coord + 21)){
			if(mode){
				deplp(&p2, coord, coord + 21);
				if(!echec(p2,c))
					ajoutercoup(lscoup, coord + 21);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + 21);
		}
		break;

		case 10: //Pion Blanc
		if(coord/10 == 6){
			if(p.grille[o - 2][a] == -1 && p.grille[o - 1][a] == -1){
				if(mode){
					deplp(&p2, coord, coord - 20);
					if(!echec(p2,0))
						ajoutercoup(lscoup, coord - 20);
					p2 = p;
				}
				else
					ajoutercoup(lscoup, coord - 20);
			}
		}
		if(p.grille[o - 1][a] == -1){
			if(mode){
				deplp(&p2, coord, coord - 10);
				if(!echec(p2,0))
					ajoutercoup(lscoup, coord - 10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - 10);
		}
		if((p.grille[o - 1][a - 1])%2 == 1 && coordvalide(coord - 11)){
			if(mode){
				deplp(&p2, coord, coord - 11);
				if(!echec(p2,0))
					ajoutercoup(lscoup, coord - 11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - 11);
		}
		if((p.grille[o - 1][a + 1])%2 == 1 && coordvalide(coord - 9)){
			if(mode){
				deplp(&p2, coord, coord - 9);
				if(!echec(p2,0))
					ajoutercoup(lscoup, coord - 9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord - 9);
		}
		break;

		case 11: //Pion Noir
		if(coord/10 == 1){
			if(p.grille[o + 2][a] == -1 && p.grille[o + 1][a] == -1){
				if(mode){
					deplp(&p2, coord, coord + 20);
					if(!echec(p2,1))
						ajoutercoup(lscoup, coord + 20);
					p2 = p;
				}
				else
					ajoutercoup(lscoup, coord + 20);
			}
		}
		if(p.grille[o + 1][a] == -1){
			if(mode){
				deplp(&p2, coord, coord + 10);
				if(!echec(p2,1))
					ajoutercoup(lscoup, coord + 10);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + 10);
		}
		if((p.grille[o + 1][a - 1])%2 == 0 && coordvalide(coord + 9)){
			if(mode){
				deplp(&p2, coord, coord + 9);
				if(!echec(p2,1))
					ajoutercoup(lscoup, coord + 9);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + 9);
		}
		if((p.grille[o + 1][a + 1])%2 == 0 && coordvalide(coord + 11)){
			if(mode){
				deplp(&p2, coord, coord + 11);
				if(!echec(p2,1))
					ajoutercoup(lscoup, coord + 11);
				p2 = p;
			}
			else
				ajoutercoup(lscoup, coord + 11);
		}
		break;

		default:
		break;
	}
}

void initlscoup(int lscoup[27]){
	int i;
	for(i=0 ; i<27 ; i++)
		lscoup[i] = -1;
}

void ajoutercoup(int lscoup[27], int coord){
	int i;
	for(i=0 ; lscoup[i] != -1 && i<27 ; i++){}
	lscoup[i] = coord;
}

char itoc(int n){
	switch(n){
		case 0:
		return 'A';
		case 1:
		return 'B';
		case 2:
		return 'C';
		case 3:
		return 'D';
		case 4:
		return 'E';
		case 5:
		return 'F';
		case 6:
		return 'G';
		default:
		return 'H';
	}
}

int echec(plateau p, int couleur){ //c (0 = blanc / 1 = noir)
	int r = -1;
	int i,j,x;
	int lscoup[27];
	for(i=0 ; i<8 && r == -1 ; i++){
		for(j=0 ; j<8 && r == -1 ; j++){
			if(p.grille[i][j] == couleur){
				r = i*10 + j;
			}
		}
	}
	int t = p.grille[r/10][r%10];
	if (t == 0){ //Roi blanc
		if(	(p.grille[r/10 - 1][r%10] 	== 1	&& coordvalide(r - 10))	||
			(p.grille[r/10 - 1][r%10 - 1] == 1	&& coordvalide(r - 11))	||
			(p.grille[r/10 - 1][r%10 + 1] == 1	&& coordvalide(r - 9))	||
			(p.grille[r/10][r%10 - 1] 	== 1	&& coordvalide(r - 1))	||
			(p.grille[r/10][r%10 + 1] 	== 1	&& coordvalide(r + 1))	||
			(p.grille[r/10 + 1][r%10 - 1] == 1	&& coordvalide(r + 9)) 	||
			(p.grille[r/10 + 1][r%10 + 1] == 1	&& coordvalide(r + 11))	||
			(p.grille[r/10 + 1][r%10] 	== 1	&& coordvalide(r + 10))) {	
			return 1;
		}
	}
	if (t == 1){ //Roi blanc
		if(	(p.grille[r/10 - 1][r%10] 	== 0	&& coordvalide(r - 10))	||
			(p.grille[r/10 - 1][r%10 - 1] == 0	&& coordvalide(r - 11))	||
			(p.grille[r/10 - 1][r%10 + 1] == 0	&& coordvalide(r - 9))	||
			(p.grille[r/10][r%10 - 1] 	== 0	&& coordvalide(r - 1))	||
			(p.grille[r/10][r%10 + 1] 	== 0	&& coordvalide(r + 1))	||
			(p.grille[r/10 + 1][r%10 - 1] == 0	&& coordvalide(r + 9)) 	||
			(p.grille[r/10 + 1][r%10 + 1] == 0	&& coordvalide(r + 11))	||
			(p.grille[r/10 + 1][r%10] 	== 0	&& coordvalide(r + 10))) {	
			return 1;
		}
	}

	if(couleur)
		couleur = 0;
	else couleur = 1;

	for(i=0 ; i<8 ; i++){
		for(j=0 ; j<8 ; j++){
			if((p.grille[i][j])%2 == couleur && p.grille[i][j] != couleur){
				initlscoup(lscoup);
				coupslegaux(p, i*10 + j, lscoup, 0);
				for(x=0 ; lscoup[x] != -1 ; x++){
					if (lscoup[x] == r){
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int mat(plateau p, int couleur){ //c (0 = blanc / 1 = noir)
	int i,j,k;
	int lscoup[27];
	plateau p2;
	p2 = p;
	for(i=0 ; i<8 ; i++){
		for(j=0 ; j<8 ; j++){
			if(p.grille[i][j]%2 == couleur){
				initlscoup(lscoup);
				coupslegaux(p2, i*10 + j, lscoup, 0);
				for(k=0 ; lscoup[k] != -1 ; k++){
					deplp(&p2, i*10 + j, lscoup[k]);
					if(!echec(p2, couleur)){
						return 0;
					}
					p2 = p;
				}
			}
		}
	}
	return 1;
}

arbre initarbre(){
	arbre a = malloc(sizeof(noeud));
	a->coup = -1;
	a->suiv[0] = NULL;
	return a;
}

void inserefeuille (arbre a, int coord, int c){
	int i;
	arbre b;
	for (i = 0;; i++){
		if (! (a->suiv[i])) {
			b = malloc (sizeof(noeud));
			b->coord = coord;
			b->coup = c;
			b->suiv[0] = NULL;
			a->suiv[i] = b;
			a->suiv[i+1] = NULL;
			return;
		}
	}
}

void inserearbre (arbre a, arbre b, int coord, int c){
	int i;
	for (i = 0;; i++){
		if (! (a->suiv[i])){
			a->suiv[i] = b;
			a->suiv[i]->coord = coord;
			a->suiv[i]->coup = c;
			a->suiv[i+1]=NULL;
			return;
		}
	}
}

void afficherarbre(arbre a, int nbc){
	int i;
	for(i=0 ; a->suiv[i]!=NULL ; i++){
		if(i)
			printf("OU\n");
		printf("coup %d : %c%d va en %c%d\n", nbc, itoc(a->suiv[i]->coord%10), 8 - a->suiv[i]->coord/10, itoc(a->suiv[i]->coup%10), 8 - a->suiv[i]->coup/10);
		afficherarbre(a->suiv[i], nbc + 1);
	}
	if(!a->suiv[0])
		printf("Echec et mat !!!\n");
}