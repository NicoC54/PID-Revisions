
//My first work on PID class

class PID{

    public:
        double Kp;
        double Ki;
        double Kd;
        double previous_error=0;
        double integral_sum =0;

    PID(double Kp, double Ki, double Kd){
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
    }
    
    
    float ApplyPID(double error, double dt){
        double proportionnal_correction = Kp*error;
        double integral_correction = Ki*error * dt;
        double derivative_correction = Kd* (error-previous_error)/dt;
        previous_error = error;

        return proportionnal_correction + integral_correction + derivative_correction;




    }

};


class PID {

    public:
        double Kp;
        double Ki;
        double Kd;
        double previous_error = 0;
        // AJOUT : Il manquait une variable pour mémoriser la somme accumulée de l'intégrale
        double integral_sum = 0.0;

    PID(double Kp, double Ki, double Kd) {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
    }
    
    // ANCIENNE LIGNE : float ApplyPID(double Kp, double Ki, double Kd, double error){
    // CORRECTION :
    // 1. Inutile de repasser Kp, Ki, Kd (ils sont déjà stockés dans 'this').
    // 2. Il manquait le paramètre 'dt' (intervalle de temps).
    // 3. Préférer 'double' à 'float' pour rester cohérent avec le reste de la classe.
    double ApplyPID(double error, double dt) {

        // AJOUT : Sécurité pour éviter une division par zéro si dt est nul ou négatif
        if (dt <= 0.0) return 0.0;

        // ANCIENNE LIGNE : double proportionnal_correction = Kp*error;
        // CORRECTION : On utilise la variable membre de la classe (this->Kp ou simplement Kp)
        double proportionnal_correction = Kp * error;

        // ANCIENNE LIGNE : double integral_correction = Ki*error * dt;
        // CORRECTION : L'intégrale doit accumuler l'erreur au fil du temps (+=), sinon ce n'est qu'un rectangle unique
        integral_sum += error * dt;
        double integral_correction = Ki * integral_sum;

        // ANCIENNE LIGNE : double derivative_correction = Kd* (error-previous_error)/dt;
        // CORRECTION : La formule était bonne, mais 'dt' n'existait pas dans le scope
        double derivative_correction = Kd * (error - previous_error) / dt;

        previous_error = error;

        return proportionnal_correction + integral_correction + derivative_correction;
    }

// ANCIENNE LIGNE : }
// CORRECTION : Ne pas oublier le point-virgule à la fermeture d'une classe en C++
};