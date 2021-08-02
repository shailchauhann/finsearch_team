
#include<iostream>
#include <cmath>
#include <algorithm> 
#include <vector>  
using namespace std;
double option_price_put_european_binomial( const double& S,const double& K, const double& r, const double& sigma, const double& t, const int& steps)
{ 
double R=exp(r*(t/steps));
double  Rinv = 1.0/R;
double u = exp(sigma*sqrt(t/steps));
double uu=u*u;
double d = 1.0/u;
double p_up =(R-d)/(u-d);
double p_down = 1.0-p_up;
vector<double> prices(steps+1); 
prices[0] = S*pow(d,steps); 
for (int i=1; i<=steps; ++i) prices[i] = uu*prices[i-1];
vector<double> call_values(steps+1); 
for (int i=0; i<=steps; ++i) call_values[i] = max(0.0, (prices[i]-K)); 
for (int step=steps-1; step>=0;--step) {
for (int i=0; i<=step; ++i) {
call_values[i] = (p_up*call_values[i+1]+p_down*call_values[i])*Rinv;
};
};
return call_values[0];
};

double option_price_call_european_binomial( const double& S,const double& K, const double& r, const double& sigma, const double& t, const int& steps)
{ 
double R=exp(r*(t/steps));
double  Rinv = 1.0/R;
double u = exp(sigma*sqrt(t/steps));
double uu=u*u;
double d = 1.0/u;
double p_up =(R-d)/(u-d);
double p_down = 1.0-p_up;
vector<double> prices(steps+1); 
prices[0] = S*pow(d,steps); 
for (int i=1; i<=steps; ++i) prices[i] = uu*prices[i-1];
vector<double> put_values(steps+1); 
for (int i=0; i<=steps; ++i) put_values[i] = max(0.0, (K-prices[i])); 
for (int step=steps-1; step>=0;--step) {
for (int i=0; i<=step; ++i) {
put_values[i] = (p_up*put_values[i+1]+p_down*put_values[i])*Rinv;
};
};
return put_values[0];
};
 
 int main()
 {
double S;
double K; 
double r; 
double sigma;
double t; 
 int steps;
 cout<<" Enter Strike price ";
 cin>>S;
 cout<<"\n Enter Stock price ";
 cin>>K;
 cout<<"\n Enter risk free interest rate ";
 cin>>r;
 cout<<"\n Enter volatility ";
 cin>>sigma;
 cout<<"\n Enter time to maturity(in year) ";
 cin>>t;
cout<<"\n Enter no of steps in binomial tree ";
 cin>>steps; 
 double x=option_price_put_european_binomial(S,K,r,sigma,t,steps);
 cout<<"\n Binomial put price "<<option_price_put_european_binomial(S,K,r,sigma,t,steps);
 cout<<"\n Binomial call price "<<option_price_call_european_binomial(S,K,r,sigma,t,steps);
 
}