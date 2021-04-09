int NbMonths = ...;
range Months = 1..NbMonths;
{string} Prod = ...;
{string} Process = ...; 

int ProfitProd[Prod] = ...;
float ProcessProd[Process][Prod] = ...;
int MarketProd[Months][Prod] = ...;

float CostHold = ...;
int StartHold = ...;
int EndHold = ...;
int MaxHold = ...;

int HoursMonth = ...;
int NumProcess[Process] = ...;
int NumDown[Process] = ...;

// number of machines down in each month
dvar int+ MonthDown[Process][Months];
// number of products to be 
// made, sell, hold in each month
dvar int+ MonthMake[Prod][Months];
dvar int+ MonthSell[Prod][Months];
// Sell at the month could not exceed the sum of 
// the hold in the previous month and 
// the make in the current month.
// So it is a nonnegative integer.
dvar int+ MonthHold[Prod][Months];

maximize
	sum(p in Prod)
	  sum(m in Months)
	    (MonthSell[p][m] * ProfitProd[p] 
	    	- MonthHold[p][m] * CostHold);	  	
subject to {
	// The relation of Hold between months.
	forall (p in Prod)
	  forall (m in Months)
	  	ctHold:
	  		MonthHold[p][m] == 
	  			// No Stock at the beginning.
	  			(m==1 ? StartHold : MonthHold[p][m-1]) 
	  			+ MonthMake[p][m] - MonthSell[p][m];
	  			
	// The maximum hold for every month.
	forall (p in Prod)
	  	forall (m in Months)
	  	  	ctMaxHold:
	  	  		MonthHold[p][m] <= MaxHold;
	  		
	// Exactly 50 stocks for every product at the end of June.
	forall (p in Prod)
	  	ctEndHold:
	  		MonthHold[p][6] == EndHold;

	// Every Month should be down once.
	forall (q in Process)
	  	ctDown:
	  		sum(m in Months)
	  		  	MonthDown[q][m] == NumDown[q];
	
	// Time limitation
	forall (q in Process)
	  forall (m in Months)
	  	ctWork:
			sum (p in Prod)
			  MonthMake[p][m] * ProcessProd[q][p] <= 
			  	(NumProcess[q] - MonthDown[q][m]) * HoursMonth;
	
	// Marketing limitation
	forall (p in Prod)
	  forall (m in Months)
	    ctMarket:
	    	MonthSell[p][m] <= MarketProd[m][p];
}

float TotalSellingProfit = 
	sum(p in Prod)
	  sum(m in Months)
	  	MonthSell[p][m] * ProfitProd[p];
	  	
float TotalHoldingCost = 
	sum(p in Prod)
	  sum(m in Months)
	  	MonthHold[p][m] * CostHold;

float TotalNetProfit = 
	TotalSellingProfit - TotalHoldingCost;

execute{
	writeln("Total Selling Profit=", TotalSellingProfit);
	writeln("Total Holding Cost=", TotalHoldingCost);
	writeln("Total Net Profit=", TotalNetProfit);
}