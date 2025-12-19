/*********************************************************************
 * @file  Jeu.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef JEU_H_
#define JEU_H_

/**
  * @class Jeu
  * @brief Classe Jeu
*/    
class Jeu
{
  public :
    /**
     * @fn Jeu();
     * @brief Constructeur par defaut
    */    
    Jeu();
    /**
     * @fn Jeu();
     * @brief Destructeur
    */    
    ~Jeu();    
    /**
     * @fn void init(void)
     * @brief Fonction d'initialisation de l'application
    */
    void init(void);
    /**
     * @fn void run(void)
     * @brief Fonction de lancement de l'application
    */
    void run(void);
};
#endif