import pandas as pd
import numpy as np
import math
from math import exp, sqrt
from scipy.stats import norm
df = pd.read_csv("TATAMOTORS.csv")
df = df.sort_values(by="Date")
df = df.dropna()
# calculate returns
df = df.assign(close_day_before=df.Close.shift(1))
df['returns'] = np.log(df.Close)
newdf=df['returns']

vardata= newdf.var(0)
standard_deviation= np.sqrt(vardata)





def black_scholes_call(S, K, T, r, sigma):
    d1 = (np.log(S/K) + (r+(np.power(sigma,2))/2)*T)/(sigma*np.sqrt(T))
    d2 = d1 - sigma * np.sqrt(T)
    return (S * norm.cdf(d1)) - ((K*np.exp(-r*T))*norm.cdf(d2))

def black_scholes_put(S, K, T, r, sigma):
    d1 = (np.log(S/K) + (r+vardata/2)*T)/(sigma*np.sqrt(T))
    d2 = d1 - sigma * np.sqrt(T)
    return  ((K*np.exp(-r*T))*norm.cdf(-d2)) -(S * norm.cdf(-d1))






dx= 0.00001

S= float(input("Spot price: "))
K=float(input("Strike Price: "))
T=float(input("Time left in days: "))
r=float(input("Rate: "))
market_price=float(input("Market price for the call: "))
market_price2=float(input("Market price for the put: "))



def implied_volatility_call(MP):
    X = standard_deviation


    result = black_scholes_call(S, K, T/356, r, X)

    if result >= MP :
        while (black_scholes_call(S,K,T/356,r,X)-MP) >= 0.001:
            X -= dx
        else:

            return X
    else :
        while (MP - black_scholes_call(S,K,T/356,r,X)) >= 0.0001:
            X += dx
        else:
            return X
def implied_volatility_Put(MP):
    X = standard_deviation


    result = black_scholes_put(S, K, T/356, r, X)

    if result >= MP :
        while (black_scholes_put(S,K,T/356,r,X)-MP) >= 0.001:
            X -= dx
        else:

            return X
    else :
        while (MP - black_scholes_put(S,K,T/356,r,X)) >= 0.0001:
            X += dx
        else:
            return X




print('Black_Scholes Model Price for the call option: ')
print(black_scholes_call(S,K,T/356,r,standard_deviation))
print('Annual Volatility is:  ')
print(100*standard_deviation)
print('Implied Volatility_Call is: ')
print(100*implied_volatility_call(market_price))
print('Black_Scholes Model Price for the PUT option:')
print(black_scholes_put(S,K,T/356,r,standard_deviation))
print('Implied Volatility_PUT is: ')
print(100*implied_volatility_Put(market_price2))




