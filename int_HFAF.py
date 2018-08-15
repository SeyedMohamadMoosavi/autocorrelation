#! /usr/bin/env python

from scipy.integrate import quad
import scipy.special as special
import numpy as np
import math
import matplotlib.pyplot as plt


f_k_data=open('kappa.out','w')
f_in=open('autocorrelation.dat','r')
data_in=f_in.readlines()
len_data=len(data_in)
labels=['crystal','x','y','z']
Ks=[]
for i in [1,2,3,4]:
    int_set=[]
    int_set_average=[]
    f_out=open('int_HFACF_%i.dat'%i,'w')
    int_range=[int(p) for p in np.linspace(0.01*len_data,len_data,1000)]
    for j in int_range:
        y_data_used=np.array([float(a.strip().split()[i]) for a in data_in[1:j]])
        integral=1e9*np.trapz(y_data_used)
        int_set.append(integral)
        int_set_average.append(np.mean(int_set))
        f_out.write("%f\n"%(int_set[-1]))
    plt.plot(int_set,label='%s'%labels[i-1],linewidth=0.2,alpha=0.6)
    plt.plot(int_set_average,label='average %s'%labels[i-1],linewidth=2)
    
    f_k_data.write('Thermal conducvitiy in %-10s = %5.4f\n'%(labels[int(i)-1],np.average(int_set_average[-200:-100])))    
    Ks.append(np.average(int_set_average[400:600]))


f_k_data.write('max / min thermal conducvitiy is = %5.4f\n'%(max(Ks[1:])/min(Ks[1:])))    

plt.xlabel('time (t)')
plt.ylabel(r'$\frac{1}{k_B VT^2}\int_{0}^{t}<J(t) . J(0)>dt$')
plt.ylim([0,20*max(Ks[1:])])
plt.legend()
plt.savefig('integral_HFAUF.png',dpi=300)
