#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#define black_text "\x1b[30m"
#define red_text "\x1b[31m"
#define gray_text "\x1b[90m"
#define purple_text "\033[0;35"
#define white_background "\x1b[47m"
#define reset_color "\x1b[0m"
#define italic "\x1b[3m"
#define blue_text "\033[1;34m"
#define green_text "\033[1;32m"

int days_in_shamsi[] = {0,31,31,31,31,31,31,30,30,30,30,30,29,29};

void clearScreen()
{
    system("cls");
}

int intPart(double value)
{
    if (value < 0) {
        // Subtract 0.5 and convert to an integer if the value is less than 0
        return (int)(value - 0.5);
    } else {
        // Add 0.5 and convert to an integer if the value is greater than or equal to 0
        return (int)(value + 0.5);
    }
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void invalidInput()
{
    printf("\n%s\n", red_text "Invalid input! Please enter a correct choice" reset_color);
    printf("\nPress Enter valid input again: ");
    clearInputBuffer();
    getchar();
    //clearScreen();
}

void calenderMenue()
{
        printf("\n%s", black_text white_background "               Calendar Menu               \n" reset_color);
        printf("\n Back to menue [0]\n\n");
        printf(green_text"Calendar Year is between 1206 to 1498\n\n"reset_color);
        printf(green_text"Calendar month is between 1 to 12\n"reset_color);
        printf("\nPlease enter the year: ");
}

int InputYear(void)
{
    int year;
    do
    {
        calenderMenue();

        scanf("%d", &year);
        if (year == 0)
        {
            return 0;
        }
        if (year < 1206 || year > 1498)
        {
            invalidInput();
        }
    } while (year < 1206 || year > 1498);

    return year;
}

int InputMonth(int year)
{
    int month;
    do
    {
        printf("Please enter the month:");
        if(scanf("%d", &month) != 1)
        {
            invalidInput();
            break;
        }
        if (month == 0)
        {
            return 0;
        }
        if (month < 1 || month > 12)
        {
            invalidInput();

            year = InputYear();

        if (year == 0)
        {     
        return 0;
        }
        }

    } while (month < 1 || month > 12);

    return month;
}

int day_code(int year, int month)
{
    int daycode = (year * 365 + (year / 4) + 1) % 7;

    if (year >= 1206 && year <= 1218)
    {
        daycode += 2;
    }

    if (year >= 1208 && year <= 1218 && year != 1211 && year != 1215)
    {
        daycode = (daycode - 1) % 7;
    }

    if (year == 1219)
    {
        daycode = (daycode + 2) % 7;
    }

    if (year >= 1220 && year < 1300)
    {
        daycode = (daycode + 1) % 7;
    }

    for (int i = 1; i < month; i++)
    {
        daycode = (daycode + days_in_shamsi[i]) % 7;
    }

    return daycode;
}


int determineLeapYear(int y) {
    int matches[] = {1, 5, 9, 13, 17, 22, 26, 30};
    int modulus = y - ((y / 33) * 33);
    int K = 0;

    for (int n = 0; n != 8; n++) {
        if (matches[n] == modulus) {
            K = 1;
            break;
        }
    }

    return K;
}
int determineLeapYearMiladi(int year)
{
    if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
        return 1; 
    else
        return 0; 
}



char *shamsi_monthes[] = {
    " ",
    purple_text white_background "               FARVARDIN              "reset_color,
    purple_text white_background "               ORDIBEHESH             "reset_color,
    purple_text white_background "                KHORDAD               "reset_color,
    purple_text white_background "                 TIR                  "reset_color,
    purple_text white_background "                 MORDAD               "reset_color,
    purple_text white_background "               SHAHRIVAR              "reset_color,
    purple_text white_background "                MEHR                  "reset_color,
    purple_text white_background "                 ABAN                 "reset_color,
    purple_text white_background "                 AZAR                 "reset_color,
    purple_text white_background "                 DEY                  "reset_color,
    purple_text white_background "                BAHMAN                "reset_color,
    purple_text white_background "               ESFAND                 "reset_color
};

void calendar(int year, int month, int dayCode)
{
    int day;
    
    if(determineLeapYear(year) == 0)
    {
        days_in_shamsi[12] = 29;
    }
    
    else if(determineLeapYear(year) == 1)
    {
        days_in_shamsi[12] = 30;
    }
    
       printf("\n%s\n\n%s    %s    %s    %s    %s    %s    %s\n\n",
           shamsi_monthes[month],

           gray_text "SH" reset_color,
           gray_text "YE" reset_color,
           gray_text "DO" reset_color,
           gray_text "SE" reset_color,
           gray_text "CH" reset_color,
           gray_text "PA" reset_color,
           gray_text "JO" reset_color
    );
    
    for(day = 1; day <= dayCode; day++)
    {
        printf("      ");
    }
    for(day = 1; day <= days_in_shamsi[month]; day++)
    {

        printf("%-6d", day);

        if ((day + dayCode) % 7 == 0 || day == days_in_shamsi[month])
        {
            
            printf("\n");
        }
    }

    printf("\n%s%d%s\n", black_text white_background "---------------- ",
           year,
            
           " ----------------" reset_color);
}

void shamsi_to_gregorian(int y, int m, int d, int *gYear, int *gMonth, int *gDay)
{
    int sumShamsi[] = {31, 62, 93, 124, 155, 186, 216, 246, 276, 306, 336, 365};
    int gregorianDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int yy, mm, dayCount;
    dayCount = d;
    if (m > 1)
        
        dayCount = dayCount + sumShamsi[m - 2];

    
    yy = y + 621;
    
    dayCount = dayCount + 79;

    if (determineLeapYearMiladi(yy) == 1)
    {
        if (dayCount > 366)
        {
   
            dayCount = dayCount - 366;
            
            yy = yy + 1;
        }
    }
    else if (dayCount > 365)
    {
        // Adjust the day count if it exceeds the number of days in a non-leap year
        dayCount = dayCount - 365;
        // Increment the year by 1
        yy = yy + 1;
    }

    if (determineLeapYearMiladi(yy) == 1)
        // Adjust the number of days in February if the year is a leap year
        gregorianDays[1] = 29;

    mm = 0;
    while (dayCount > gregorianDays[mm])
    {
        // Subtract the number of days in the current month
        dayCount = dayCount - gregorianDays[mm];
        // Increment the month by 1
        mm = mm + 1;
    }

    *gYear = yy; 
    *gMonth = mm + 1; 
    *gDay = dayCount;
}

void gregorianToShamsi(int year, int month, int day, int *sYear, int *sMonth, int *sDay)
{
    int countDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i, dayYear;
    int newMonth, newYear, newDay;

    dayYear = 0;
    for (i = 1; i < month; i++)
    {
        // Calculate the total number of days in the Gregorian calendar from the start of the year to the given date
        dayYear = dayYear + countDays[i - 1];
    }
    dayYear = dayYear + day;

    if (determineLeapYear(year) && month > 2)
        // Add 1 to the day count if the year is a leap year and the month is greater than February
        dayYear = dayYear + 1;

    if (dayYear <= 79)
    {
        if ((year - 1) % 4 == 0)
        {
            /*
             * Calculate the day count based on the special rule for
             the Shamsi calendar when the day count is less than or equal to 79
             */
            dayYear = dayYear + 11;
        }
        else
        {
            dayYear = dayYear + 10;
        }

        // Calculate the year in the Shamsi calendar by subtracting 622
        newYear = year - 622;
        if (dayYear % 30 == 0)
        {
            // Calculate the month in the Shamsi calendar when the day count is divisible by 30
            newMonth = (dayYear / 30) + 9;
            newDay = 30;
        }
        else
        {
            // Calculate the month in the Shamsi calendar when the day count is not divisible by 30
            newMonth = (dayYear / 30) + 10;
            newDay = dayYear % 30;
        }
    }
    else
    {
        // Calculate the year in the Shamsi calendar by subtracting 621
        newYear = year - 621;
        dayYear = dayYear - 79;

        if (dayYear <= 186)
        {
            if (dayYear % 31 == 0)
            {
                // Calculate the month in the Shamsi calendar when the day count is divisible by 31
                newMonth = dayYear / 31;
                newDay = 31;
            }
            else
            {
                // Calculate the month in the Shamsi calendar when the day count is not divisible by 31
                newMonth = (dayYear / 31) + 1;
                newDay = dayYear % 31;
            }
        }
        else
        {
            dayYear = dayYear - 186;

            if (dayYear % 30 == 0)
            {
                // Calculate the month in the Shamsi calendar when the day count is divisible by 30
                newMonth = (dayYear / 30) + 7;
                newDay = 30;
            } else
            {
                // Calculate the month in the Shamsi calendar when the day count is notdivisible by 30
                newMonth = (dayYear / 30) + 8;
                newDay = dayYear % 30;
            }
        }
    }

    *sYear = newYear; // Store the converted year in the provided pointer
    *sMonth = newMonth; // Store the converted month in the provided pointer
    *sDay = newDay; // Store the converted day in the provided pointer
}

void gregorianToLunar(int year, int month, int day, int *lYear, int *lMonth, int *lDay)
{
    int juliandate;

    if (year > 1582 || (year == 1582 && (month > 10 || (month == 10 && day >= 15))))
    {
        juliandate = intPart((1461 * (year + 4800 + intPart((month - 14) / 12))) / 4)
                     + intPart((367 * (month - 2 - 12 * intPart((month - 14) / 12))) / 12)
                     - intPart((3 * intPart((year + 4900 + intPart((month - 14) / 12)) / 100)) / 4)
                       // Calculate the Julian date using the Gregorian date formula
                     + day - 32075;
    }
    else
    {
        juliandate = 367 * year
                     - intPart((7 * (year + 5001 + intPart((month - 9) / 7))) / 4)
                     + intPart((275 * month) / 9)
                       // Calculate the Julian date using the pre-Gregorian date formula
                     + day + 1729777;
    }

    int l = juliandate - 1948440 + 10632;
    int n = intPart((l - 1) / 10631);
    l = l - 10631 * n + 354;

    int j = (intPart((10985 - l) / 5316)) * (intPart((50 * l) / 17719))
            + (intPart(l / 5670)) * (intPart((43 * l) / 15238));

    l = l - (intPart((30 - j) / 15)) * (intPart((17719 * j) / 50))
            // Perform calculations to determine the Lunar date
        - (intPart(j / 16)) * (intPart((15238 * j) / 43)) + 29;

    int lunarM = intPart((24 * l) / 709);
    int lunarD = l - intPart((709 * lunarM) / 24);
    int lunarY = 30 * n + j - 30;

    *lYear = lunarY; // Store the converted year in the provided pointer
    *lMonth = lunarM; // Store the converted month in the provided pointer
    *lDay = lunarD; // Store the converted day in the provided pointer
}

void date_conversion_menu()
{
    printf(black_text white_background"          Date Conversion Menu          \n"reset_color);
    printf("\n\n [0]Back to menu!\n\n [1]Shamsi to Gregorian/Lunar\n\n [2]Gregorian to Shamsi/Lunar");
    printf(black_text, white_background"\n----------------------------------------"reset_color);
    printf("\n%s\nselect option: ");
}

int date_conversion(void)
{
    int option;
    int sh_year, sh_month, sh_day;
    int gYear, gMonth, gDay;
    int lYear, lMonth, lDay;

    do
    {
        clearScreen();

        date_conversion_menu();

        if(scanf("%d", &option) !=1)
        {
            invalidInput();
            continue;;
        }
        switch(option)
        {
            case 0:
                return -1;
                break;
            case 1:
            printf("[0] Get back to menu\n");
            printf("\nShamsi year is between 1206 to 1498");
            printf("\nShamsi month is between 1 to 12");
            printf("\nShamsi day is between 1 to 31");
            printf("\n\nEnter the shamsi year:");

                if(scanf("%d", &sh_year) != 1 || sh_year < 0)
                {
                    invalidInput();
                    break;
                }
                if(sh_year == 0)
                {
                    return -1;
                }
                printf("Enter the shamsi month:");
                if(scanf("%d", &sh_month) != 1 || sh_month <1 || sh_month >12)
                {
                    invalidInput();
                    break;
                }
                printf("Enter the shamsi day:");
                if(scanf("%d", &sh_day) != 1 || sh_day <1 || sh_day > days_in_shamsi[sh_month])
                {
                    invalidInput();
                    break;
                }
                
                shamsi_to_gregorian(sh_year, sh_month, sh_day, &gYear, &gMonth, &gDay);
                gregorianToLunar(gYear, gMonth, gDay, &lYear, &lMonth, &lDay);
                

                clearScreen();

                printf("\nThe converted date in gregorian is %d/%02d/%02d\n", gYear, gMonth, gDay);
                printf("\nThe converted date in lunar is %d/%02d/%02d\n",lYear, lMonth, lDay);
                printf("\nPress Enter to continue");
                clearInputBuffer();
                getchar();
                break;
            case 2:
                clearScreen();
                printf("[0] Get back to menu\n");
                printf("\nEnter the gregorian year:");
                if (scanf("%d", &gYear) != 1 || gYear < 0)
                {
                    invalidInput();
                    break;
                }
                
                if(gYear == 0)
                {
                    return -1;
                }
                
                printf("\n\nEnter the gregorian month:");
                if(scanf("%d", &gMonth) != 1 || gMonth <1 || gMonth > 12)
                {
                    invalidInput();
                    break;
                }
                printf("\n\nEnter the gregorian day:");
                if(scanf("%d", &gDay) != 1 || gDay <1 || gDay > days_in_shamsi[gMonth])
                {
                    invalidInput();
                    break;
                }
                gregorianToShamsi(gYear, gMonth, gDay, &sh_year, &sh_month, &sh_day);

                gregorianToLunar(gYear, gMonth, gDay, &lYear, &lMonth, &lDay);

                clearScreen();
                printf("\n\n Converted date to shamsi is  %d/%02d/%02d",sh_year, sh_month, sh_day);
                printf("\n\n Converted date to lunar is  %d/%02d/%02d\n", lYear, lMonth, lDay);
                printf("\n\nPress Enter to continue");
                clearInputBuffer();
                getchar();
                break;
                default :
                printf("\n\nInvalid choice");
                printf("\nPress enter to continue");
                clearInputBuffer();
                getchar();
                break;
        }
        

        
    }while(option !=0);
    return 0;
}

struct tm getCurrentDateAndTime(){
    time_t t = time(NULL);
    struct tm current_date = *localtime(&t);
    return current_date;
}

void age_menu()
{
    printf("\n%s", black_text white_background "                Age Menu              \n" reset_color);
    printf("\n%s Back to menu!\n",gray_text "[0]" reset_color);
}

void calculate_age(int birth_year, int birth_month, int birth_day)
{

clearScreen();
struct tm current_date = getCurrentDateAndTime();
    int current_gregorian_year = current_date.tm_year + 1900;
    int current_gregorian_month = current_date.tm_mon;
    int current_gregorian_day = current_date.tm_mday;

    int current_year, current_month, current_day;

    gregorianToShamsi(current_gregorian_year, current_gregorian_month, current_gregorian_day,&current_year, &current_month, &current_day);

    if(birth_month <1 || birth_month >12)
    {
        invalidInput();
        return;
    }
    if(birth_day <1 || birth_day > days_in_shamsi[birth_month])
    {
        invalidInput();
        return;
    }

    int age_years = current_year - birth_year;
    int age_months = current_month - birth_month;
    int age_days = current_day - birth_day;

    if(age_days < 0 )
    {
        age_months--;
        age_days += days_in_shamsi[current_month];
    }
    if(age_months <0)
    {
        age_years--;
        age_months += 12;
    }
    int birth_daycode = day_code(birth_year, birth_month);
    int birth_day_of_week = (birth_daycode + birth_day - 1) % 7;

    if (age_years < 0)
    {
        clearScreen();
        printf("\n%s.\n\n", red_text "Please enter a year between 1 and 1402" reset_color);
        return;
    }

    char *shamsi_week_days[] = {"SHANBEH", "YEKSHANBEH", "DOSHANBEH", "SESHANBEH", "CHAHARSHANBEH", "PANJSHANBEH", "JOMEH"};
    char *geo_week_days[]= {"SATURDAY", "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY"};
     int geo_day, geo_month, geo_year;
     shamsi_to_gregorian(birth_year, birth_month, birth_day, &geo_year, &geo_month, &geo_day);
     birth_year = geo_year;
     birth_month = geo_month;
     birth_day  = geo_day;

     time_t birth_time = mktime(&(struct tm){0, 0, 0, birth_day, birth_month - 1, birth_year - 1900});
     time_t current_time = mktime(&current_date); 
    int lived_seconds = difftime(current_time, birth_time);
    int lived_days = lived_seconds / (60 * 60 * 24) ; 

    printf("\n You have lived: %d years, %d months, %d days" ,age_years, age_months, age_days);
    printf("\n\n The week day of your birthday in shamsi calendar is %s", shamsi_week_days[birth_day_of_week]);
    printf("\n\n Number of days that you have lived is %d", lived_days, reset_color);
    printf("\n\n Your birth date in georgian is %d/%02d/%02d",geo_year, geo_month, geo_day);
    printf("\n\n The week day of your birthday in gregorian calendar is %s\n\n",geo_week_days[birth_day_of_week]);

}

int age(void)
{
    int bDay, bMonth, bYear;

    do
    {
        clearScreen();
        age_menu();
        printf("\nEnter your birth year:");
        if(scanf("%d", &bYear) != 1)
        {
            invalidInput();
            continue;
        }
        if(bYear == 0)
        {
            return 0;
        }
        if(bYear < 1)
        {
            invalidInput();
            continue;
        }
        printf("Enter your birth month:");
        if(scanf("%d", &bMonth) != 1)
        {
            invalidInput;
            continue;
        }
        if(bMonth == 0)
        {
            return 0;
        }
        if(bMonth <1 || bMonth >12)
        {
            invalidInput();
            continue;
        }
        printf("Enter your birth day:");
        if(scanf("%d", &bDay) != 1)
        {
            invalidInput();
            continue;
        }
        if(bDay == 0)
        {
            return 0;
        }
        if(bDay <1 || bDay >days_in_shamsi[bMonth])
        {
            invalidInput();
            break;
        }
        calculate_age(bYear, bMonth, bDay);
        printf(" Press Enter to continue");
        clearInputBuffer();
        getchar();
    }while(1);
}

int main(void)
{
    int vorodi;
    int shamsi_year, shamsi_month, shamsi_daycode;

    do
    {
        clearScreen();

               printf("\n%s\n%s Quit\n\n%s Calendar\n\n%s Age Calculation\n\n%s Date Conversion\n\n%s\n ",
               black_text white_background "                 Menu                 \n" reset_color,
               blue_text "[0]" reset_color,
               blue_text "[1]" reset_color,
               blue_text "[2]" reset_color,
               blue_text "[3]" reset_color,
               black_text white_background "---------------------------------------" reset_color,
               reset_color);
        printf(" select option: ");

        if(scanf("%d", &vorodi) != 1)
        {
            invalidInput;
            continue;
        }
        switch (vorodi)
        {
        case 0:
            clearScreen();
            printf(green_text "Bye bye...SEE U AGAIN! \n");
            sleep(2);
            break;
        
        case 1:
                do{
                shamsi_year = InputYear();
                if(shamsi_year == 0)
                {
                    break;
                }
                shamsi_month = InputMonth(shamsi_year);
                if(shamsi_month == 0)
                {
                    break;
                }
                
                shamsi_daycode = day_code(shamsi_year, shamsi_month);

                calendar(shamsi_year, shamsi_month, shamsi_daycode);
                
                printf("\n");
            }while(1);
            break;
        case 2:
                clearScreen();
                age();
            break;
        case 3:
                clearScreen();
                date_conversion();
                break;
        default:
                if (vorodi != 0 && vorodi != 1 && vorodi != 2 && vorodi != 3)
                {
                    printf("\n%s\n", red_text "Invalid choice!" reset_color);
                    printf("\ndPress Enter to try again...");
                    clearInputBuffer();
                    getchar();
                }
            break;
        } 
    }while(vorodi != 0);
    return 0;
}