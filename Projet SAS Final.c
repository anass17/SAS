#include <stdio.h>

struct etudiant {
	int numero;
	char nom[30];
	char prenom[30];
	char dateNaissance[11];
	int departement;
	float note;
};

typedef struct etudiant etudiant;

void menuPrincipal();
int ajouterEtudiant(etudiant tab[], int total);

int main() {
	etudiant listeEtudiants[100];
	int totalEtudiant = 0;
	int choix;
	
	char departements[30][30];
	int departmentsCount = 0;
	
	while (1) {
		menuPrincipal();
		scanf("%d", &choix);
		
		switch(choix) {
			case 1:
				ajouterEtudiant(listeEtudiants, totalEtudiant, departements, departmentsCount);
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
	printf("7. Trier un etudiant\n");
	printf("\n-->  ");
}

int ajouterEtudiant(etudiant tab[], int total, ) {
	int choix;
	
	printf("\n");
	printf("-------------------\n");
	printf("---   L'ajout   ---\n");
	printf("-------------------\n");
	printf("\n");
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
			printf("Numero unique:  ");
			scanf("%d", &tab[total].numero);
			printf("Nom:            ");
			scanf("%s", tab[total].nom);
			printf("Prenom:         ");
			scanf("%s", tab[total].prenom);
			printf("Date de naissance (yyyy-mm-dd):  ");
			scanf("%s", tab[total].dateNaissance);
			printf("Department:     \n");
			scanf("%d", &tab[total].departement);
			printf("Note generale:  ");
			scanf("%f", &tab[total].note);
			printf("\nL'etudiant \"%s %s\" a ete ajoute\n", tab[total].prenom, tab[total].nom);
			return ++total;
		}
		if (choix == 2) {
			printf("\n");
			printf("------------------------------------------\n");
			printf("---   Ajouter des nouveaux etudiants   ---\n");
			printf("------------------------------------------\n");
			printf("\n");
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
