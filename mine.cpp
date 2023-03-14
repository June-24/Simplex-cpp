#include <bits/stdc++.h>
using namespace std;

int constraints;
vector<double> obj_fun;
int ent_var(vector<double> &obj_fun, int variables)
{
    int max = INT_MAX;
    int index = 0;
    for (int i = 0; i < variables; i++)
    {
        if (max > obj_fun[i])
            max = obj_fun[i], index = i;
    }
    return index;
}
int leav_var(vector<vector<double>> &Tableau, int ent_var, int constraints, int &variables)
{
    int max = INT_MAX;
    int j = -1;
    for (int i = 0; i < constraints; i++)
    {
        if (Tableau[i][ent_var] * Tableau[i][variables] <= 0 || Tableau[i][variables] < 0)
            continue;
        if (max > (Tableau[i][variables] / Tableau[i][ent_var]))
            max = (Tableau[i][variables] / Tableau[i][ent_var]), j = i;
    }
    return j;
}
void Make_it_one_The_leaving_variable(int leaving_variable, vector<vector<double>> &Tableau, double pivot)
{
    for (int i = 0; i < Tableau[leaving_variable].size(); i++)
        Tableau[leaving_variable][i] /= pivot;
}
void Gauss_Jordon(vector<vector<double>> &Tableau, vector<double> &updated_row, int enter_var, int leaving_var, vector<double> &obj_fun)
{
    for (int i = 0; i < Tableau.size(); i++)
    {
        if (i == leaving_var)
            continue;
        double coeff = Tableau[i][enter_var];
        for (int j = 0; j < Tableau[0].size(); j++)
            Tableau[i][j] = Tableau[i][j] - coeff * updated_row[j];
    }
    double coeff = obj_fun[enter_var];
    for (int i = 0; i < obj_fun.size(); i++)
        obj_fun[i] = obj_fun[i] - coeff * updated_row[i];
}
int main()
{
    cout << "Enter the number of variables : ";
    int variables;
    cin >> variables;
    cout << "Enter the number of Constraints : ";
    cin >> constraints;
    obj_fun.resize(variables + 1 + constraints, 0);
    cout << "Enter the coefficients of the objective function  :";
    for (int i = 0; i <= variables; i++)
        cin >> obj_fun[i];
    vector<vector<double>> Tableau(constraints, vector<double>(variables + 1 + constraints));
    for (int i = 0; i < constraints; i++)
    {
        cout << "Enter the coefficients of Constraint number: " << i + 1 << endl;
        for (int j = 0; j <= variables; j++)
            cin >> Tableau[i][j];
        Tableau[i][variables + i + 1] = 1;
    }
    cout << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "The Given Objective Function is: z = ";
    for (int i = 0; i < variables; i++)
        if (obj_fun[i] < 0)
            cout << "+" << -1 * obj_fun[i] << "X" << i + 1 << " ";
        else
            cout << obj_fun[i] << "X" << i + 1 << " ";
    cout << endl;
    cout << "The Given Constraints are: " << endl;
    for (int i = 0; i < constraints; i++)
    {
        int j = 0;
        for (j = 0; j < variables; j++)
            if (Tableau[i][j] >= 0)
                cout << "+" << Tableau[i][j] << "X" << j + 1 << " ";
            else
                cout << Tableau[i][j] << "X" << j + 1 << " ";

        cout << "<=" << Tableau[i][j] << " " << endl;
    }
    cout << "---------------------------------------------------" << endl;
    cout << endl;
    int temp = variables;
    while (temp--)
    {
        int entering_value = ent_var(obj_fun, variables);
        int leaving_variable = leav_var(Tableau, entering_value, constraints, variables);
        Make_it_one_The_leaving_variable(leaving_variable, Tableau, Tableau[leaving_variable][entering_value]);
        vector<double> updated_row = Tableau[leaving_variable];
        Gauss_Jordon(Tableau, updated_row, entering_value, leaving_variable, obj_fun);
    }
    cout << "The optimal value of Z is: ";
    cout << obj_fun[variables] - 1 << endl;
    for (int i = 0; i < variables; i++)
        cout << "The optimal value of x" << i + 1 << " is: " << Tableau[i][variables] << endl;
    return 0;
}