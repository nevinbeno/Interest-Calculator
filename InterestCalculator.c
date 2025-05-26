#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void validate(double principal_amount, double interest_rate, int months)
{
    if (principal_amount < 0)
    {
        printf("\nERROR : principal amount should not be below ZERO.");
        exit (EXIT_FAILURE);
    }
    else if (interest_rate < 0)
    {
        printf("\nERROR : Interest Rate should not be below ZERO");
        exit (EXIT_FAILURE);
    }
    else if (months <= 0)
    {
        printf("\nERROR : Time in months should be greater than ZERO");
        exit (EXIT_FAILURE);
    }
}

double simpleInterest(double principal_amount, double interest_rate, int months)
{
    double time = months/12.0;//for making the correct division arithmatic
    double simple_interest = (principal_amount * interest_rate * time)/100;
    return simple_interest;
}
double compoundInterest(double principal_amount, double interest_rate, int months, int frequency)
{
    double time = months/12.0;
    double A = principal_amount * (pow(1 + (interest_rate/(100.0 * frequency)), frequency * time));
    return (A - principal_amount);
}
int main ()
{
    static int j = 1;// for printing the iteration to file
    int i = 1;// for controlling the loop running
    FILE *fptr = NULL;
    do
    {
        int operation;// for getting which interest to calculate
        double principal_amount, interest_rate;
        int months;

        printf("Enter the details : ");
        printf("\nprincipal Amount (in Rupees): ");
        scanf("%lf", &principal_amount);
        printf("\nAnnual Interest Rate (percentage): ");
        scanf("%lf", &interest_rate);
        printf("\nTime (in months): ");
        scanf("%d", &months);

        validate(principal_amount, interest_rate, months);

        printf("%-20s%-20s%-20s\n", "Sl.no", "Calculate", "Code");
        printf("%-20d%-20s%-20d\n", 1, "Simple Interest", 1);
        printf("%-20d%-20s%-20d\n", 2, "Compound Interest", 2);
        printf("Enter the code of the operation you want to perform (refer the above table) : ");
        scanf("%d", &operation);
    
        double interest;
        if (j == 1)
        {
            fptr = fopen("record.txt", "w");
        }
        else
        {
            fptr = fopen("record.txt", "a");
        }
        if (fptr == NULL)
        {
            printf("ERROR : Couldn't log transaction. Please restart and try again.");
            return EXIT_FAILURE;
        }
        fprintf(fptr, "Iteration %d: \n\n", j);
        fprintf(fptr, "Principal amount = Rs. %.2lf\nAnnual Interest Rate (in percentage)= %.2lf \nTime in months = %d\n", principal_amount,
        interest_rate, months);
        switch (operation)
        {
            case 1:
                interest = simpleInterest(principal_amount, interest_rate, months);
                printf("\nSimple Interest = Rs.  %.2lf\nTotal Amount = Rs.  %.2lf", interest, interest + principal_amount);
                fprintf(fptr, "Simple Interest = Rs. %.2lf\nTotal Amount = Rs. %.2lf\n", interest, interest + principal_amount);
                break;
            case 2:
            {
                int frequency; 
                printf("\n\n%-20s%-20s\n", "Frequency", "Code");
                printf("%-20s%-20d\n", "Annually", 1);
                printf("%-20s%-20d\n", "Half - yearly", 2);
                printf("%-20s%-20d\n", "Quarterly", 4);
                printf("%-20s%-20d\n", "Monthly", 12);
                printf("\nPlease enter the compounding frequency, (refer the table above) : ");
                scanf("%d", &frequency);
                if (frequency != 1 && frequency != 2 && frequency != 4 && frequency != 12)
                {
                    printf("\nERROR : Please enter a valid frequency.");
                    return EXIT_FAILURE;
                }
                interest = compoundInterest(principal_amount, interest_rate, months, frequency);
                printf("\nCompound Interest = Rs. %.2lf\nTotal Amount = Rs.  %.2lf", interest, interest + principal_amount);
                fprintf(fptr, "Compounding frequency factor = %d\n", frequency);
                fprintf(fptr, "Compound Interest = Rs. %.2lf\nTotal Amount = Rs. %.2lf\n", interest, interest + principal_amount);
                break;
            }        
            default:
                printf("\nERROR : Invalid operation code. Please restart and try again.");
                return EXIT_FAILURE;
        }
        j++;
        fprintf(fptr,"\n");
        fclose(fptr);
        fptr = NULL;
        printf("\nEnter 0 to exit, or any value to continue : ");
        scanf("%d", &i);
    } while (i);
    printf("\nProgram Ends.");
    return 0;
}