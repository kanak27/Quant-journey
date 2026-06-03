#include <iostream>
#include <cmath>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

static double Cdf(double x)
{
    return 0.5 * erfc((-x) / sqrt(2));
}

static double Pdf(double x)
{
    return exp(-0.5 * x * x) / sqrt(2.0 * M_PI);
}

class Option
{
    private:
        double const strike;
        double const expiry;
        double const spot;
        double const vol;
        double const rate;

        double CalculateD1() const
        {
            double numerator1 = log(spot / strike);
            double numerator2 = (rate + (0.5 * vol * vol)) * expiry;
            double denominator = vol * sqrt(expiry); 

            return (numerator1 + numerator2) / denominator;
        }

    public:
        double getStrike() const { return strike; }
        double getExpiry() const { return expiry; }
        double getSpot() const { return spot; }
        double getVol() const { return vol; }
        double getRate() const { return rate; }

        Option(double k, double t, double s, double sigma, double r):
            strike { k }, expiry { t }, spot { s }, vol { sigma}, rate { r }
        {
        }

        double price() const
        {
            // Black Scholes
            // C = S * N(d1) - K * exp(-rT) * N(d2)
            // d1 = (ln(S / K) + (r + 0.5 * sigma^2) * T) / (sigma * sqrt(T))
            // d2 = (ln(S / K) - (r + 0.5 * sigma^2) * T) / (sigma * sqrt(T)) = d1 - sigma * sqrt(T)
            // C: Call option price
            // S: Stock price
            // K: Exercise price
            // r: risk free rate of return
            // T: Time to expiration
            // sigma: volatility, usually standard deviation
            // N(): cdf, of normal distribution
            
            double d1 = CalculateD1();
            double d2 = d1 - vol * sqrt(expiry);

            return (spot * Cdf(d1)) - (strike * Cdf(d2) * exp(-rate * expiry));
        }
        
        double delta() const
        {
            // Delta
            // sensitivity of option price to price of underlying
            // delta = N(d1) : call
            // delta = N(d1) - 1 : put
            // delta(Call) - delta(put) = 1
            // here delta is delta for call

            return Cdf(CalculateD1());
        }

        double gamma() const
        {
            // Gamma
            // sensitivity of option price to delta
            // delta = N'(d1) / (s * sigma * sqrt(T))      {N'(): pdf }

            double numerator = Pdf(CalculateD1());
            double denominator = spot * vol * sqrt(expiry);

            return numerator / denominator;
        }

        double vega() const
        {
            // Vega
            // sensitivity of option price to volatility
            // vega = S * N'(d1) * sqrt(T)

            return spot * Pdf(CalculateD1()) * sqrt(expiry);
        }

        double putPrice() const {
            return price() - spot + strike * exp(-rate * expiry);
        }
};

int main()
{
    // Option(strike, expiry, spot, vol, rate)
    Option opt(100.0, 1.0, 100.0, 0.20, 0.05);  
    cout << fixed << setprecision(7);
    cout << "Price: " << opt.price() << "\n";
    cout << "Delta: " << opt.delta() << "\n";
    cout << "Gamma: " << opt.gamma() << "\n";
    cout << "Vega: " << opt.vega() << "\n";
    cout << "Put Price: " << opt.putPrice() << "\n";
    return 0;
}