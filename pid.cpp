
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


