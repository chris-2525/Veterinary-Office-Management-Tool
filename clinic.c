#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, noRecords;

    noRecords = 0;

    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            noRecords++;
        }

        else
        {
            displayPatientData(&patient[i], fmt);
        }
    }

    if (noRecords == max)
    {
        printf("*** No records found ***\n\n");
    }

    putchar('\n');

}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do {

        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        selection = inputIntRange(0, 2);

        putchar('\n');

        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            putchar('\n');
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
            suspend();
            break;

        }

    } while (selection);

}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int newPtIndex, newPtNum;

    newPtNum = 0;
    newPtIndex = 0;

    newPtIndex = findPatientIndexByPatientNum(0, patient, max);

    if (newPtIndex == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }

    else
    {
        newPtNum = nextPatientNumber(patient, max);
        patient[newPtIndex].patientNumber = newPtNum;

        inputPatient(&patient[newPtIndex]);

        printf("*** New patient record added ***\n\n");
    }

}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNum, searchResult;

    patientNum = 0;
    searchResult = 0;

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    searchResult = findPatientIndexByPatientNum(patientNum, patient, max);

    if (searchResult != -1)
    {
        putchar('\n');
        menuPatientEdit(&patient[searchResult]);
    }

    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }

}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNum, searchResult;
    char removeAns;

    struct Patient emptyState = { 0 };

    patientNum = 0;
    searchResult = 0;
    removeAns = '\0';

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    searchResult = findPatientIndexByPatientNum(patientNum, patient, max);

    if (searchResult != -1)
    {
        putchar('\n');
        displayPatientData(&patient[searchResult], FMT_FORM);

        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");

        removeAns = inputCharOption("yn");

        if (removeAns == 'y')
        {
            patient[searchResult] = emptyState;

            printf("Patient record has been removed!\n\n");
        }

        if (removeAns == 'n')
        {
            printf("Operation aborted.\n\n");
        }
    }

    else
    {
        putchar('\n');
        printf("ERROR: Patient record not found!\n\n");
    }


}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i, j;

    bubbleSortEndBeg(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(&data->appointments->date, 1);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {

            if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
            {
                displayScheduleData(&data->patients[j], &data->appointments[i], 1);
            }

        }
    }

    putchar('\n');

}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i, j, match, found;

    struct Date date = { 0 };

    match = 0;
    found = 0;

    date = validateDate(&data->appointments->date);

    putchar('\n');

    bubbleSortEndBeg(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year == date.year
            && data->appointments[i].date.month == date.month
            && data->appointments[i].date.day == date.day)
        {
            found++;
            match = i;

            if (found == 1)
            {
                displayScheduleTableHeader(&data->appointments[match].date, 0);
            }

            for (j = 0; j < data->maxPatient; j++)
            {

                if (data->appointments[match].patientNumber ==
                    data->patients[j].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[match], 0);
                }

            }

        }


    }

    if (found == 0)
    {
        printf("ERROR: Appointment record not found!\n\n");
    }


    putchar('\n');

}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment appointment[], int maxAppointment,
    struct Patient patient[], int maxPatient)
{
    int hour, min;
    int  validTime, appointTimeAvailable, patientNumIdx, appointIndex;

    struct Date date = { 0 };

    validTime = 0;
    appointTimeAvailable = 0;

    appointIndex = nextAvailableAppointment(appointment, maxAppointment);

    if (appointIndex != -1)
    {
        printf("Patient Number: ");
        appointment[appointIndex].patientNumber = inputIntPositive();
        patientNumIdx = findPatientIndexByPatientNum(appointment[appointIndex].patientNumber,
            patient, maxPatient);

        if (patientNumIdx != -1)
        {
            do {

                date = validateDate(&appointment->date);

                do
                {
                    printf("Hour (0-23)  : ");
                    hour = inputIntRange(0, 23);

                    printf("Minute (0-59): ");
                    min = inputIntRange(0, 59);

                    validTime = validateTime(hour, min);

                } while (!validTime);

                appointTimeAvailable = findAppointTimeOption(date.year, date.month, date.day,
                    hour, min, maxAppointment,
                    appointment);

            } while (!appointTimeAvailable);
        }

        else
        {
            printf("ERROR: Patient record not found!\n\n");
        }

    }

    if (appointTimeAvailable && validTime)
    {
        appointment[appointIndex].date = date;
        appointment[appointIndex].time.hour = hour;
        appointment[appointIndex].time.min = min;

        putchar('\n');
        printf("*** Appointment scheduled! ***\n\n");
    }

}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment appointment[], int maxAppointment,
    struct Patient patient[], int maxPatient)
{
    int patientNum, patientNumIdx, removeAns, matchIdx;

    struct Appointment emptyState = { 0 };

    struct Date date = { 0 };

    matchIdx = 0;

    printf("Patient Number: ");
    patientNum = inputIntPositive();
    patientNumIdx = findPatientIndexByPatientNum(patientNum, patient, maxPatient);

    if (patientNumIdx != -1)
    {
        date = validateDate(&appointment->date);

        putchar('\n');
        displayPatientData(&patient[patientNumIdx], FMT_FORM);

        printf("Are you sure you want to remove this appointment (y,n): ");

        removeAns = inputCharOption("yn");

        matchIdx = findMatchingAppointment(patientNum, date.year, date.month, date.day,
            maxAppointment, appointment);

        if (matchIdx != -1)
        {
            if (removeAns == 'y')
            {
                appointment[matchIdx] = emptyState;

                putchar('\n');
                printf("Appointment record has been removed!\n\n");
            }

            else
            {
                printf("Operation aborted.\n\n");
            }
        }

        else
        {
            putchar('\n');
            printf("ERROR: Appointment record not found!\n\n");
        }

    }

    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }


}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////


// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNum, index;

    patientNum = 0;
    index = 0;

    printf("Search by patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index >= 0)
    {
        displayPatientData(&patient[index], FMT_FORM);
    }

    else
    {
        printf("*** No records found ***\n");
    }


}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, match;

    match = 0;

    char validPhoneNum[PHONE_LEN + 1] = { '\0' };

    printf("Search by phone number: ");
    inputCString(validPhoneNum, PHONE_LEN, PHONE_LEN);
    putchar('\n');
    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (strcmp(validPhoneNum, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            match++;
        }
    }

    if (match == 0)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }

}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, maxPtNum;

    maxPtNum = patient[0].patientNumber;

    for (i = 1; i < max; i++)
    {
        if ((patient[i].patientNumber) > maxPtNum)
        {
            maxPtNum = patient[i].patientNumber;
        }
    }

    maxPtNum = (maxPtNum + 1);

    return maxPtNum;

}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, indexMatch;

    indexMatch = -1;

    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            indexMatch = i;
        }
    }


    return indexMatch;
}


/* Find the appointment array index by  year, month, day and patient
number (returns -1 if not found)*/
int findMatchingAppointment(int patientNum, int year, int month, int day, int max,
    const struct Appointment appoints[])
{
    int searchIdx, i;

    searchIdx = -1;

    for (i = 0; i < max; i++)
    {

        if (appoints[i].patientNumber == patientNum &&
            appoints[i].date.year == year &&
            appoints[i].date.month == month &&
            appoints[i].date.day == day)

        {
            searchIdx = i;
        }
    }


    return searchIdx;

}


/*Determines if the appointment date and time inputted by the user is available,
and returns the array index if it is (returns -1 if not available) */
int findAppointTimeOption(int year, int month, int day, int hour, int min, int max,
    const struct Appointment appoints[])
{
    int i, appointTimeAvailable;

    appointTimeAvailable = 1;

    for (i = 0; i < max && appointTimeAvailable; i++)
    {

        if (appoints[i].date.year == year
            && appoints[i].date.month == month
            && appoints[i].date.day == day
            && appoints[i].time.hour == hour
            && appoints[i].time.min == min)
        {
            putchar('\n');
            printf("ERROR: Appointment timeslot is not available!\n\n");
            appointTimeAvailable = 0;

        }

    }

    return appointTimeAvailable;
}


/*Determines the appointment array index for the next available appointment*/
int nextAvailableAppointment(const struct Appointment appoint[], int max)
{

    int appointIndex, appointAvailable, i;

    appointIndex = 0;
    appointAvailable = 0;

    for (i = 0; i < max; i++)
    {
        if (appoint[i].patientNumber < 1)
        {
            appointAvailable++;
            appointIndex = i;
        }
    }


    if (appointAvailable == 0)
    {
        printf("ERROR: Appointment listing is FULL!\n\n");

        appointIndex = -1;
    }

    return appointIndex;

}

/*Determines if the hour and min inputted by user fits within clinic hours,
returns 1 if valid and 0 if not valid*/
int validateTime(int hour, int min)
{
    int validTime;

    if (min > 0 && hour <= MAX_HOUR && hour >= MIN_HOUR)
    {
        if (hour == MAX_HOUR)
        {
            validTime = 0;
        }

        else if (min % MINUTE_INT)
        {
            validTime = 0;
        }

        else
        {
            validTime = 1;
        }

    }

    else
    {
        if (hour > MAX_HOUR || hour < MIN_HOUR)
        {
            validTime = 0;

        }

        else
        {
            validTime = 1;
        }
    }

    if (!validTime)
    {
        printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n",
            MIN_HOUR, MAX_HOUR, MINUTE_INT);
    }

    return validTime;

}

//Validates the year, month and day inputted by the user, returns a Date struct type 
struct Date validateDate(struct Date date[])
{
    struct Date result = { 0 };

    printf("Year        : ");
    result.year = inputIntRange(YEAR_MIN, YEAR_MAX);

    printf("Month (1-12): ");
    result.month = inputIntRange(1, 12);

    result.day = validateDay(result.year, result.month);

    return result;
}

//sorts data in ascending order by date and time 
void bubbleSortEndBeg(struct Appointment appoint[], int maxAppt)
{
    int j, i;

    struct Appointment temp = { 0 };

    for (i = 0; i < maxAppt; i++)
    {
        appoint[i].time.min = (appoint[i].time.min) + (appoint[i].date.year * 60 * 24 * 30 * 12) +
            (appoint[i].date.month * 60 * 24 * 30) +
            (appoint[i].date.day * 60 * 24) +
            (appoint[i].time.hour * 60);
    }

    for (j = maxAppt - 1; j > 0; j--)
    {
        for (i = 0; i < j; i++)
        {
            if (appoint[i].time.min > appoint[i + 1].time.min)
            {
                temp = appoint[i];
                appoint[i] = appoint[i + 1];
                appoint[i + 1] = temp;
            }
        }
    }

    for (i = 0; i < maxAppt; i++)
    {
        appoint[i].time.min = (appoint[i].time.min) - (appoint[i].date.year * 12 * 30 * 24 * 60) -
            (appoint[i].date.month * 30 * 24 * 60) -
            (appoint[i].date.day * 24 * 60) -
            (appoint[i].time.hour * 60);
    }

}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n"
        "------------------\n");

    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;

    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");

    selection = inputIntRange(0, 4);

    putchar('\n');

    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL");
        break;

    case 2:
        strcpy(phone->description, "HOME");
        break;

    case 3:
        strcpy(phone->description, "WORK");
        break;

    case 4:
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "0");
        break;
    }

    if (selection != 4)
    {
        printf("Contact: ");
        printf("%s", phone->description);
        putchar('\n');
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
    }


}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* fp = fopen("patientData.txt", "r");
    int i = 0;

    if (fp != NULL)
    {

        while (fscanf(fp, "%d|%15[^|]|%4[^|]|%10[^\n]\n", &patients[i].patientNumber,
            patients[i].name,
            patients[i].phone.description,
            patients[i].phone.number) >= 3 && i < max)
        {
            i++;
        }

        fclose(fp);
        fp = NULL;

    }

    else
    {
        puts("ERROR: Failed to access file!");
    }


    return i;



}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{

    FILE* fp = fopen("appointmentData.txt", "r");
    int i;

    i = 0;


    if (fp != NULL)
    {

        while (fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patientNumber,
            &appoints[i].date.year,
            &appoints[i].date.month,
            &appoints[i].date.day,
            &appoints[i].time.hour,
            &appoints[i].time.min) == 6 && i < max)
        {
            i++;
        }

        fclose(fp);
        fp = NULL;
    }
    else
    {
        puts("ERROR: Failed to access file!");
    }


    return i;



}

