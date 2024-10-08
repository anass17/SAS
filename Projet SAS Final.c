#include <stdio.h>
#include <string.h>

struct etudiant {
	int numero;
	char nom[30];
	char prenom[30];
	char dateNaissance[11];
	int departement;
	float note;
};

typedef struct etudiant etudiant;

int IDcounter = 13;

void menuPrincipal();
int ajouterEtudiant(etudiant tab[], int total, char dep[][30], int *depCount);
void afficherEtudiants(etudiant tab[], int total, char dep[][30]);
void modifierEtudiant(etudiant tab[], int total, char dep[][30], int *depCount);
int supprimerEtudiant(etudiant tab[], int total);
int calculMoyenne(etudiant tab[], int total, char dep[][30], int depCount);
void rechercherEtudiant(etudiant tab[], int total, char dep[][30], int depCount);
void statistiques(etudiant tab[], int total, char dep[][30], int depCount);
void trierEtudiants(etudiant tab[], int total, char dep[][30]);
int ajoute(etudiant tab[], int total, char dep[][30], int *depCount);

int main() {
	etudiant listeEtudiants[100] = 
	{
		{1, "Boutaib", "Anass", "2001-03-06", 0, 17.75}, 
		{2, "Samih", "Mohamed", "2006-02-07", 1, 16}, 
		{3, "Chahbone", "Achraf", "1998-06-23", 0, 16.5},
		{4, "Asami", "Fatiha", "1999-07-13", 1, 12},
		{5, "Sarab", "Youssef", "2003-05-12", 1, 18.6},
		{6, "Fahim", "Ahmed", "2002-06-22", 1, 9.75},
		{7, "Labid", "Abdelmalek", "2000-11-25", 0, 18.75},
		{8, "Edderkaoui", "Oussama", "1998-11-21", 0, 16.25},
		{9, "Ait mokhtar", "Abdelhafid", "2003-10-01", 0, 14.5},
		{10, "Taoudi", "Ahmad", "2002-09-21", 4, 12.75},
		{11, "Bourhman", "Karima", "1999-03-11", 3, 7.5},
		{12, "Saadaoui", "Ali", "1998-11-28", 3, 6.45},
	};
	int totalEtudiant = 12;
	int choix;
	
	char departements[30][30] = {"Informatique", "Mathematique", "Chimie", "Physique", "Biologie"};
	int departementsCount = 5;
	
	while (1) {
		menuPrincipal();
		scanf("%d", &choix);
		
		switch(choix) {
			case 1:
				totalEtudiant = ajouterEtudiant(listeEtudiants, totalEtudiant, departements, &departementsCount);
				break;
			case 2:
				printf("\nVous voulez:\n");
				printf("1. Modifier les information d'un etudiant\n");
				printf("2. Supprimer un etudiant\n");
				printf("0. Annuler cet operation\n");
				printf("\n-->  ");
				scanf("%d", &choix);
				if (choix == 1) {
					modifierEtudiant(listeEtudiants, totalEtudiant, departements, &departementsCount);
				} else if (choix == 2) {
					totalEtudiant = supprimerEtudiant(listeEtudiants, totalEtudiant);
				} else {
					printf("\nL'operation a ete annuler\n");
				}	
				break;
			case 3:
				afficherEtudiants(listeEtudiants, totalEtudiant, departements);	
				break;
			case 4:
				calculMoyenne(listeEtudiants, totalEtudiant, departements, departementsCount);
				break;
			case 5:
				statistiques(listeEtudiants, totalEtudiant, departements, departementsCount);
				break;
			case 6:
				rechercherEtudiant(listeEtudiants, totalEtudiant, departements, departementsCount);
				break;
			case 7:
				trierEtudiants(listeEtudiants, totalEtudiant, departements);
				break;
			case 0:
				printf("\nMerci pour l'utilisation de ce programme. Au revoir!\n");
				return;
			default: 
				printf("\nCe choix n'est pas valable\n");
		}
	}
	
	return 0;
}

void menuPrincipal() {
	printf("\n");
	printf("-----------------------------\n");
	printf("---   Le menu principal   ---\n");
	printf("-----------------------------\n");
	printf("\n");
	printf("1. Ajouter un etudiant\n");
	printf("2. Modifier ou supprimer un etudiant\n");
	printf("3. Afficher les details d'un etudiant\n");
	printf("4. Calculer la moyenne generale\n");
	printf("5. Statistiques\n");
	printf("6. Rechercher un etudiant\n");
	printf("7. Trier les etudiants\n");
	printf("0. Sortir\n");
	printf("\n-->  ");
}

void afficherEtudiants(etudiant tab[], int total, char dep[][30]) {
	int i;
	char nomComplete[61];
	
	printf("+----------------------------------------------------------------------------------------------+\n");
	printf("| %-10s | %-30s | %-10s | %-20s | %-10s |\n", "No.", "Nom Complete", "Naissance", "Departement", "Note");
	printf("+----------------------------------------------------------------------------------------------+\n");
	for (i = 0; i < total; i++) {
		strcpy(nomComplete, tab[i].nom);
		strcat(nomComplete, " ");
		strcat(nomComplete, tab[i].prenom);
		printf("| %-10d | %-30s | %-10s | %-20s | %-10.2f |\n", tab[i].numero, nomComplete, tab[i].dateNaissance, dep[tab[i].departement], tab[i].note);
		printf("+----------------------------------------------------------------------------------------------+\n");
	}
}

int ajoute(etudiant tab[], int total, char dep[][30], int *depCount) {
	int year, month, day, i, depTemp;
	
	tab[total].numero = IDcounter++;
	printf("Nom:            ");
	scanf("%s", tab[total].nom);
	printf("Prenom:         ");
	scanf("%s", tab[total].prenom);
	
	// Date de naissance
	
	while (1) {
		
		printf("Date de naissance (yyyy-mm-dd):  ");
		if (scanf("%4d-%2d-%2d", &year, &month, &day) != 3) {
			printf("\nLe format de la date de naissance est incorrect\n\n");
			scanf("%*s");
			continue;
		} else if (year < 1980 || month < 1 || month > 12 || day < 1 || day > 31) {
			printf("\nLe format de la date de naissance est incorrect\n\n");
			scanf("%*[^\n]");
			getchar();
			continue;
		}
		sprintf(tab[total].dateNaissance, "%4d-%02d-%02d", year, month, day);
		break;
	}
	
	// Departement
	
	while (1) {
		
		printf("\nVeuillez selectionnez ou ajouter un nouveau departement:\n");
		for (i = 0; i < *depCount; i++) {
			printf("%d. %s\n", i + 1, dep[i]);
		}
		printf("0. Lier l'etudiant a un nouveau departement\n");
		printf("\n-->  ");
		scanf("%d", &depTemp);
		
		if (depTemp > 0 && depTemp <= *depCount) {
			tab[total].departement = depTemp - 1;
			break;
		} else if (depTemp == 0) {
			printf("Entrer le nom de ce nouveau departement:  ");
			scanf("%s", dep[*depCount]);
			tab[total].departement = *depCount;
			(*depCount)++;
			printf("\nLe nouveau departement a ete ajoute\n\n");
			break;
		} else {
			printf("\n### ( ! ) Veillez choisir un parmi les departement valable ou ajouter un nouveau ###\n");
		}
	}
	
	// Note Generale
	
	tab[total].note = -1;
	while (tab[total].note < 0 || tab[total].note > 20) {
		printf("Note generale:  ");
		scanf("%f", &tab[total].note);	
	}
	
	printf("\nL'etudiant(e) \"%s %s\" a ete ajoute\n\n", tab[total].prenom, tab[total].nom);
}

int ajouterEtudiant(etudiant tab[], int total, char dep[][30], int *depCount) {
	int choix, j, nbr;
	
	
	printf("\n");
	printf("--------------------\n");
	printf("---   L'ajoute   ---\n");
	printf("--------------------\n");
	printf("\n");
	
	if (total >= 100) {
		printf("( ! ) Le programme ne peut pas ajouter d'autres etudiants\n");
		return total;	
	}
	
	printf("1. Ajouter un etudiant\n");
	printf("2. Ajouter plusieurs etudiants\n");
	printf("0. Annuler\n");
	while (1) {
		
		printf("\n-->  ");
		
		scanf("%d", &choix);
		
		if (choix == 1) {
			printf("\n");
			printf("---------------------------------------\n");
			printf("---   Ajouter un nouveau etudiant   ---\n");
			printf("---------------------------------------\n");
			printf("\n");
			printf("Veuillez entrer les information de ce nouveau etudiant\n");
			
			ajoute(tab, total, dep, depCount);
			
			return ++total;
		}
		if (choix == 2) {
			printf("\n");
			printf("------------------------------------------\n");
			printf("---   Ajouter des nouveaux etudiants   ---\n");
			printf("------------------------------------------\n");
			printf("\n");
			
			printf("Combien d'etudiants vous voulez ajouter?  ");
			scanf("%d", &nbr);
			
			if (total + nbr > 100) {
				printf("\n( ! ) Le programme peut ajouter juste %d etudiant(s)\n", 100 - total);
			}
			
			printf("\nVeuillez entrer les information des nouveaux etudiants\n\n");
			
			for (j = 0; j < nbr; j++) {
				printf("Nouveau etudiant #%d\n", j + 1);
				ajoute(tab, total, dep, depCount);
				total++;
			}
			return total;
		}
		if (choix == 0) {
			printf("\nL'operation a ete annuler\n");
			return;
		} else {
			printf("\nCe choix n'est pas valable\n");
		}
	}
}

void modifierEtudiant(etudiant tab[], int total, char dep[][30], int *depCount) {
	int nbrUnique, choix, depTemp, i;
	
	printf("\n");
	printf("--------------------------------\n");
	printf("---   Modifier un etudiant   ---\n");
	printf("--------------------------------\n");
	printf("\n");
	
	printf("Veuillez entrer le numero unique de l'etudiant a modidfier:  ");
	scanf("%d", &nbrUnique);
	
	int j = 0;
	
	while (j < total && nbrUnique != tab[j].numero) {
		j++;
	}
	
	if (j == total) {
		printf("\nCet etudiant ne se trouve pas\n");
		return;
	}
	
	printf("\nLes details de cet etudiant:\n");
	printf("Numero unique:      %d\n", tab[j].numero);
	printf("Nom Complete:       %s %s\n", tab[j].prenom, tab[j].nom);
	printf("Date de naissance:  %s\n", tab[j].dateNaissance);
	printf("Departement:        %s\n", dep[tab[j].departement]);
	printf("Note:               %.2f\n", tab[j].note);
	printf("\n\n");
	
	while (1) {
		printf("Modifier:\n");
		printf("1. Nom\n");
		printf("2. Prenom\n");	
		printf("3. Date de naissance\n");
		printf("4. Departement\n");
		printf("5. Note generale\n");
		printf("0. Annuler\n");
		printf("\n-->  ");
		scanf("%d", &choix);
		
		if (choix == 1) {
			printf("\nEntrer le nouveau nom:  ");
			scanf("%s", tab[j].nom);
			printf("\nLe nom d'etudiant du numero %d a ete modifier\n", tab[j].numero);
			break;
		} else if (choix == 2) {
			printf("\nEntrer le nouveau prenom:  ");
			scanf("%s", tab[j].prenom);
			printf("\nLe prenom d'etudiant du numero %d a ete modifier\n", tab[j].numero);
			break;
		} else if (choix == 3) {
			printf("\nEntrer la nouvelle date de naissance (yyyy-mm-dd):  ");
			scanf("%s", tab[j].dateNaissance);
			printf("\nLa date de naissance d'etudiant \"%s %s\" a ete modifier\n", tab[j].prenom, tab[j].nom);
			break;
		} else if (choix == 4) {
			while (1) {
				printf("\nVeuillez selectionnez ou ajouter un nouveau departement:\n");
				for (i = 0; i < *depCount; i++) {
					printf("%d. %s\n", i + 1, dep[i]);
				}
				printf("0. Lier l'etudiant a un nouveau departement\n");
				printf("\n-->  ");
				scanf("%d", &depTemp);
				
				if (depTemp > 0 && depTemp <= *depCount) {
					tab[j].departement = depTemp - 1;
					break;
				} else if (depTemp == 0) {
					printf("Entrer le nom de ce nouveau departement:  ");
					scanf("%s", dep[*depCount]);
					tab[j].departement = *depCount;
					(*depCount)++;
					printf("\nLe nouveau departement a ete ajoute\n\n");
					break;
				} else {
					printf("\n### ( ! ) Veillez choisir un parmi les departement valable ou ajouter un nouveau ###\n");
				}
			}
			printf("\nLe departement d'etudiant \"%s %s\" a ete modifier\n", tab[j].prenom, tab[j].nom);
			break;
		} else if (choix == 5) {
			printf("\nEntrer la nouvelle note generale:  ");
			scanf("%f", &tab[i].note);
			printf("\nLa note generale d'etudiant \"%s %s\" a ete modifier\n", tab[j].prenom, tab[j].nom);
			break;
		} else if (choix == 0) {
			printf("\nL'operation a ete annuler\n");
			return;
		} else {
			printf("\n### ( ! ) Ce choix n'est pas valables###\n");
		}
	}
	
	printf("\nLes nouveaux details de cet etudiant:\n");
	printf("Numero unique:      %d\n", tab[j].numero);
	printf("Nom Complete:       %s %s\n", tab[j].prenom, tab[j].nom);
	printf("Date de naissance:  %s\n", tab[j].dateNaissance);
	printf("Departement:        %s\n", dep[tab[j].departement]);
	printf("Note:               %.2f\n", tab[j].note);
	
}

int supprimerEtudiant(etudiant tab[], int total) {
	int nbrUnique;
	char fullName[61];
	
	printf("\n");
	printf("---------------------------------\n");
	printf("---   Supprimer un etudiant   ---\n");
	printf("---------------------------------\n");
	printf("\n");
	
	printf("Veuillez entrer le numero unique de l'etudiant a supprimer:  ");
	scanf("%d", &nbrUnique);
	
	int i = 0;
	
	while (i < total && tab[i].numero != nbrUnique) {
		i++;
	}
	
	if (i == nbrUnique) {
		printf("\nL'etudiant ne se trouve pas\n");
		return total;
	}
	
	strcpy(fullName, tab[i].prenom);
	strcat(fullName, " ");
	strcat(fullName, tab[i].nom);
	
	for (i = i; i < total - 1; i++) {
		tab[i] = tab[i + 1];
	}
	total--;
	
	printf("\nL'etudiant(e) \"%s\" a ete supprimer\n", fullName);
	
	return total;
}

int calculMoyenne(etudiant tab[], int total, char dep[][30], int depCount) {
	int i;
	float depSomme[30] = {0};
	int countEtudiant[30] = {0};
	float sommeGenerale = 0;
	int countGeneral = 0;
	
	printf("\n");
	printf("------------------------------\n");
	printf("---   Calcul des moyennes  ---\n");
	printf("------------------------------\n");
	printf("\n");
	
	for (i = 0; i < total; i++) {
		depSomme[tab[i].departement] += tab[i].note;
		countEtudiant[tab[i].departement]++;
		sommeGenerale += tab[i].note;
		countGeneral++;
	}
	
	printf("+------------------------------------------------------------------------------+\n");
	printf("| %-30s | %-20s | %-20s |\n", "Departement", "Nombre d'etudiants", "La moyenne generale");
	printf("+------------------------------------------------------------------------------+\n");
	for (i = 0; i < depCount; i++) {
		if (countEtudiant[i] != 0) {
			printf("| %-30s | %-20d | %-20.2f |\n", dep[i], countEtudiant[i], depSomme[i]/countEtudiant[i]);
		} else {
			printf("| %-30s | %-20d | %-20.2f |\n", dep[i], 0, 0);
		}
		printf("+------------------------------------------------------------------------------+\n");
	}
	if (countGeneral == 0) {
		countGeneral = 1;
	}
	printf("\nLa moyenne generale de l'universite est: %.2f\n", sommeGenerale / countGeneral);
	
}

void rechercherEtudiant(etudiant tab[], int total, char dep[][30], int depCount) {
	int i, choix;
	int trouver = 0;
	char nomRech[61];
	int depChoix;
	char nomComplete[61];
	
	printf("\n");
	printf("---------------------------------\n");
	printf("---   Rechercher un etudiant  ---\n");
	printf("---------------------------------\n");
	printf("\n");
	
	printf("Choisir un option:\n");
	printf("1. Rechercher un etudiant\n");
	printf("2. Afficher la liste des etudiants inscrits dans un departement specifique\n");
	printf("\n-->  ");
	scanf("%d", &choix);
	
	if (choix == 1) {
		printf("Entrer le nom de cet etudiant:  ");
		getchar();
		scanf("%[^\n]", nomRech);
		getchar();
		
		for (i = 0; i < total; i++) {
			strcpy(nomComplete, tab[i].prenom);
			strcat(nomComplete, " ");
			strcat(nomComplete, tab[i].nom);
			if (strstr(nomComplete, nomRech) != NULL) {
				printf("Numero unique:      %d\n", tab[i].numero);
				printf("Nom Complete:       %s %s\n", tab[i].prenom, tab[i].nom);
				printf("Date de naissance:  %s\n", tab[i].dateNaissance);
				printf("Departement:        %s\n", dep[tab[i].departement]);
				printf("Note:               %.2f\n", tab[i].note);
				printf("\n");
				trouver = 1;
			}
		}
		if (trouver == 0) {
			printf("\nAucun etudiant trouver\n");
		}
	} else if (choix == 2) {
		printf("\nAfficher les etudiants inscrits dans la departement de:\n");
		for (i = 0; i < depCount; i++) {
			printf("%d. %s\n", i + 1, dep[i]);
		}
		printf("\n-->  ");
		scanf("%d", &depChoix);
		
		for (i = 0; i < total; i++) {
			if (tab[i].departement == (depChoix - 1)) {
				printf("Numero unique:      %d\n", tab[i].numero);
				printf("Nom Complete:       %s %s\n", tab[i].prenom, tab[i].nom);
				printf("Date de naissance:  %s\n", tab[i].dateNaissance);
				printf("Departement:        %s\n", dep[tab[i].departement]);
				printf("Note:               %.2f\n", tab[i].note);
				printf("\n");
				trouver = 1;
			}
		}
		if (trouver == 0) {
			printf("\nAucun etudiant est inscrit dans le departement \"%s\"\n", dep[depChoix - 1]);
		}
	} else {
		printf("\nCe choix n'est pas valide\n");
	}
}

void statistiques(etudiant tab[], int total, char dep[][30], int depTotal) {
	int choix, i;
	float seuil;
	int trouver = 0;
	int depCount[30] = {0};
	int meilleures[2][3];
	
	printf("\n");
	printf("-----------------------\n");
	printf("---   Statistiques  ---\n");
	printf("-----------------------\n");
	printf("\n");
	
	printf("\nVeuillez choisir un choix parmi les options suivants:\n");
	printf("1. Afficher le nombre total d'etudiants inscrits\n");
	printf("2. Afficher le nombre d'etudiants dans chaque departement\n");
	printf("3. Afficher les etudiants ayant une moyenne generale superieure a un certain seuil\n");
	printf("4. Afficher les 3 etudiants ayant les meilleures notes\n");
	printf("5. Afficher le nombre d'etudiants ayant reussi dans chaque departement\n");
	printf("\n-->  ");
	scanf("%d", &choix);
	
	switch(choix) {
		case 1:
			printf("Le nombre total d'etudiants: %d\n", total);
			break;
		case 2:
			printf("\nLe nombre d'etudiants dans chaque departement:\n");
			for(i = 0; i < total; i++) {
				depCount[tab[i].departement]++;
			}
			for(i = 0; i < depTotal; i++) {
				printf("%-15s: %d\n", dep[i], depCount[i]);
			}
			break;
		case 3:
			seuil = -1;
			while (seuil < 0 || seuil > 20) {
				printf("\nEntrer la seuil minimale:  ");
				scanf("%f", &seuil);
			}
			printf("La liste des etudiants ayant une note generale superieur a %.2f\n\n", seuil);
			for(i = 0; i < total; i++) {
				if (tab[i].note > seuil) {
					trouver = 1;
					printf("Numero unique:      %d\n", tab[i].numero);
					printf("Nom Complete:       %s %s\n", tab[i].prenom, tab[i].nom);
					printf("Date de naissance:  %s\n", tab[i].dateNaissance);
					printf("Departement:        %s\n", dep[tab[i].departement]);
					printf("Note:               %.2f\n", tab[i].note);
					printf("\n");
				}
			}
			if (trouver == 0) {
				printf("\nAucun etudiant ayant une note superieur a %.2f\n", seuil);
			}
			
			break;
		case 4:
			
			// 0 => Notes
			// 1 => Indice
			
			meilleures[0][0] = meilleures[0][1] = meilleures[0][2] = -1;
			meilleures[1][0] = meilleures[1][1] = meilleures[1][2] = -1;
			for(i = 0; i < total; i++) {
				if (tab[i].note > meilleures[0][0]) {
					meilleures[0][2] = meilleures[0][1];
					meilleures[0][1] = meilleures[0][0];
					meilleures[0][0] = tab[i].note;
					
					meilleures[1][2] = meilleures[1][1];
					meilleures[1][1] = meilleures[1][0];
					meilleures[1][0] = i;
				} else if (tab[i].note > meilleures[0][1]) {
					meilleures[0][2] = meilleures[0][1];
					meilleures[0][1] = tab[i].note;
					
					meilleures[1][2] = meilleures[1][1];
					meilleures[1][1] = i;
				} else if (tab[i].note > meilleures[0][2]) {
					meilleures[0][2] = tab[i].note;
					
					meilleures[1][2] = i;
				}
			}
			
			printf("Les 3 meilleurs etudiants sont:\n\n");
			
			for (i = 0; i < 3; i++) {
				if (meilleures[0][i] != -1) {
					printf("Numero unique:      %d\n", tab[meilleures[1][i]].numero);
					printf("Nom Complete:       %s %s\n", tab[meilleures[1][i]].prenom, tab[meilleures[1][i]].nom);
					printf("Date de naissance:  %s\n", tab[meilleures[1][i]].dateNaissance);
					printf("Departement:        %s\n", dep[tab[meilleures[1][i]].departement]);
					printf("Note:               %.2f\n", tab[meilleures[1][i]].note);
					printf("\n");	
				}
			}
			break;
		case 5:
			for (i = 0; i < total; i++) {
				if (tab[i].note >= 10) {
					depCount[tab[i].departement]++;
				}
			}
			
			for (i = 0; i < depTotal; i++) {
				printf("%s: %d\n", dep[i], depCount[i]);
			}
			break;
		default:
			printf("\nCe choix n'est pas valid\n");
	}
}

void trierEtudiants(etudiant tab[], int total, char dep[][30]) {
	int i, j, choix;
	etudiant temp;
	etudiant reussi[100];
	int reussiCount = 0;
	etudiant nonReussi[100];
	int nonReussiCount = 0;
	
	printf("\n");
	printf("-------------------------------\n");
	printf("---   Trier les etudiants   ---\n");
	printf("-------------------------------\n");
	printf("\n");
	
	printf("\nTri les etudiants par:\n");
	printf("1. L'order alphabetique des noms\n");
	printf("2. La moyenne generale\n");
	printf("3. Leur statut de reussite\n");
	printf("0. Annuler\n");
	printf("\n-->  ");
	scanf("%d", &choix);
	
	switch (choix) {
		case 1:
			while (1) {
				printf("\nTri Les etudiants par le nom:\n");
				printf("1. De A a Z\n");
				printf("2. De Z a A\n");
				printf("0. Annuler\n");
				printf("\n-->  ");
				scanf("%d", &choix);
			
				switch (choix) {
					case 1:
						for (i = 0; i < total - 1; i++) {
							for (j = 0; j < total - i - 1; j++) {
								if (strcmp(tab[j].nom, tab[j + 1].nom) > 0) {
									temp = tab[j];
									tab[j] = tab[j + 1];
									tab[j + 1] = temp;
								}
							}
						}
						afficherEtudiants(tab, total, dep);
						return;
					case 2:
						for (i = 0; i < total - 1; i++) {
							for (j = 0; j < total - i - 1; j++) {
								if (strcmp(tab[j].nom, tab[j + 1].nom) < 0) {
									temp = tab[j];
									tab[j] = tab[j + 1];
									tab[j + 1] = temp;
								}
							}
						}
						afficherEtudiants(tab, total, dep);
						return;
					case 0:
						printf("\nL'operation a ete annuler\n");
						return;
					default:
						printf("\n( ! ) Ce choix n'est pas valide\n");
				}
			}
			break;
		case 2:
			while (1) {
				printf("\nTri Les etudiants par la moyenne generale selon l'order:\n");
				printf("1. Croissant\n");
				printf("2. Decroissant\n");
				printf("0. Annuler\n");
				printf("\n-->  ");
				scanf("%d", &choix);	
				
				switch (choix) {
					case 1:
						for (i = 0; i < total - 1; i++) {
							for (j = 0; j < total - i - 1; j++) {
								if (tab[j].note > tab[j + 1].note) {
									temp = tab[j];
									tab[j] = tab[j + 1];
									tab[j + 1] = temp;
								}
							}
						}
						afficherEtudiants(tab, total, dep);
						return;
					case 2:
						for (i = 0; i < total - 1; i++) {
							for (j = 0; j < total - i - 1; j++) {
								if (tab[j].note < tab[j + 1].note) {
									temp = tab[j];
									tab[j] = tab[j + 1];
									tab[j + 1] = temp;
								}
							}
						}
						afficherEtudiants(tab, total, dep);
						return;
					case 0:
						printf("\nL'operation a ete annuler\n");
						return;
					default:
						printf("\n( ! ) Ce choix n'est pas valide\n");
				}
			}
			break;
		case 3:
			for (i = 0; i < total; i++) {
				if (tab[i].note >= 10) {
					reussi[reussiCount++] = tab[i];
				} else {
					nonReussi[nonReussiCount++] = tab[i];
				}
			}
			
			printf("\nLa liste des etudiants qui ont reussi:\n");
			afficherEtudiants(reussi, reussiCount, dep);
			
			printf("\n\n");
			
			printf("\nLa liste des etudiants qui n'ont pas reussi:\n");
			afficherEtudiants(nonReussi, nonReussiCount, dep);

			break;
		default:
			printf("\nL'operation a ete annuler\n");
	}
	
}
