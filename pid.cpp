#include <iostream>

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

int main(){

    // Gains typiques d'un PID en vitesse (souvent dominé par P et I)
    PID speed_controller(0.08, 0.4, 0.001);

    const double target_speed = 1500.0; // Consigne : 1500 tr/min
    double current_speed = 0.0;         // Au départ, le moteur est à l'arrêt
    const double dt = 0.01;             // Boucle rapide à 100 Hz (10 ms)

    // 100 itérations = 1 seconde de fonctionnement
    for (int step = 0; step < 1000; ++step) {
        // 1. Calcul de l'erreur
        double error = target_speed - current_speed;

        // 2. Calcul de la commande PID
        double raw_cmd = speed_controller.ApplyPID(error, dt);

        // 3. Saturation du signal PWM (ex: 0 à 100% de tension moteur)
        //double pwm_duty = std::clamp(raw_cmd, 0.0, 100.0);

        // 4. Modèle physique simplifié du moteur :
        // - Le moteur accélère selon le PWM injecté
        // - Le frottement mécanique et la force contre-électromotrice freinent le moteur
        double torque_gain = raw_cmd * 250.0 * dt; // on pourrait remplacer raw_cmd par pwm_duty
        double friction_loss = current_speed * 15.0 * dt;
        current_speed += torque_gain - friction_loss;

        // Affichage tous les 10 pas (tous les 0.1s)
        if (step % 10 == 0) {
            std::cout << "t = " << step * dt << " s"
                      << " | Vitesse = " << current_speed << " tr/min"
                      << " | Erreur = " << error << " tr/min"
                      << " | Commande PWM = " << raw_cmd << " %\n";
        }
    }

    return 0;
}