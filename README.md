# So_long - Projet 42

## 📚 Description

**So_long** est un projet de l'école 42 qui consiste à réaliser un petit jeu 2D en utilisant la bibliothèque graphique MiniLibX. Le but est d'implémenter un jeu où le joueur doit collecter tous les objets présents sur une carte et atteindre la sortie en effectuant le moins de mouvements possible.

Le joueur contrôle un personnage qui se déplace sur une carte constituée de murs, d'espaces vides, d'objets à collecter et d'une sortie.

---

## 🛠️ Fonctionnalités

- Affichage graphique d'une carte 2D avec MiniLibX
- Déplacement du joueur avec les touches WASD ou les flèches directionnelles
- Collecte d'objets obligatoire avant de pouvoir sortir
- Compteur de mouvements affiché dans le terminal
- Gestion des collisions avec les murs
- Fermeture propre du programme (ESC ou croix de la fenêtre)

---

## 📂 Fichiers

- `so_long.c` : Code source principal du jeu
- `map_validation.c` : Parsing et validation des cartes
- `windows.c` : Logique du jeu et déplacements
- `map.c` : Gestion de l'affichage avec MiniLibX
- `so_long.h` : Fichier d'en-tête
- `Makefile` : Compilation du projet

---

## 🚀 Utilisation

### 1. Compilation

```bash
make
```

### 2. Lancement du jeu

```bash
./so_long <chemin_vers_carte.ber>
```

Exemple :
```bash
./so_long maps/map1.ber
```

### 3. Contrôles du jeu

- **W** ou **↑** : Déplacer vers le haut
- **A** ou **←** : Déplacer vers la gauche  
- **S** ou **↓** : Déplacer vers le bas
- **D** ou **→** : Déplacer vers la droite
- **ESC** : Quitter le jeu

---

## 🗺️ Format des cartes

Les cartes doivent être des fichiers `.ber` contenant :
- **0** : Espace vide
- **1** : Mur
- **C** : Objet à collecter
- **E** : Sortie
- **P** : Position de départ du joueur

Exemple de carte valide :
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

---

## 📝 Contraintes

- La carte doit être rectangulaire et entourée de murs
- Il doit y avoir exactement un joueur (P) et une sortie (E)
- Au moins un objet à collecter (C) doit être présent
- Tous les objets doivent être accessibles depuis la position de départ
- Utilisation exclusive de MiniLibX pour l'affichage graphique

---

## 💡 Astuces & Ressources

- Utilisez les fonctions `mlx_hook()` pour gérer les événements
- Pensez à libérer la mémoire allouée pour les textures
- Testez vos cartes avec des algorithmes de pathfinding

---

## 👤 Auteur

Projet réalisé par [asmati](https://github.com/Karten1080) dans le cadre du cursus 42.
