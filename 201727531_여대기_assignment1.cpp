
//201727531 ����� �ڷᱸ�� ����1
// Do not use 2-D array, such as int a[2][3];  
#include <iostream> 

#include <stdlib.h> 

using namespace std;

// implement the functions : add, sub, mult, transpose  
class Matrix {
public:
    Matrix(int row, int col);
    int GetData();
    Matrix Transpose();
    int Display();
    Matrix Multiply(Matrix b);
    Matrix Add(Matrix b);
    Matrix Sub(Matrix b);
    Matrix Multiply2(Matrix b);
    int CompareRowCol(Matrix b);
private:
    int rows, cols;
    int* Term;
};

Matrix::Matrix(int row, int col) : rows(row), cols(col)
{
    Term = new int[rows * cols];
}

int Matrix::GetData() {
    int input_value;
    cout << "rows = " << rows << "  cols = " << cols << endl;
    for (int j = 0; j < rows * cols; j++)
    {
        cout << "term value = ";
        cin >> input_value;
        cout << " " << endl;
        Term[j] = input_value;
    }
    return 0;
}

Matrix Matrix::Transpose() {
    Matrix b(cols, rows);

    int n = rows * cols;
    for (int i = 0; i < cols; i++)

    {
        for (int j = 0; j < rows; j++)
        {
            b.Term[i * rows + j] = Term[j * cols + i]; // Index ��ȣ�� rows �� cols �� ǥ���ϸ� rows * i + j
                                                       // ex) 3*3����� (1,2) => [5]
                                                       // ��ġ�������� j * cols +i 
        }
        //To be implemented 
    }
    cout << endl;
    return b;
}

Matrix Matrix::Multiply(Matrix b) {
    if (cols != b.rows) cout << "Incompatible matrices" << endl;
    Matrix d(rows, b.cols);
    for (int i = 0; i < rows; i++)

    {
        for (int j = 0; j < b.cols; j++)
        {
            int sum = 0; // �ʱⰪ�� 0���� ����
            for (int k = 0; k < cols; k++)
            {
               
               sum += Term[i * cols + k] * b.Term[k * b.cols + j];
               
                //����� ����
            }
            d.Term[i * b.cols + j] = sum;
            
            //To be implemented 
        }
    }
    return d;
}
Matrix Matrix::Add(Matrix b) {
    if (cols != b.cols) cout << "Incompatible matrices" << endl;
    if (rows != b.rows) cout << "Incompatible matrices" << endl;

    Matrix d(rows, cols);
    for (int i = 0; i < rows; i++)

    {
        for (int j = 0; j < cols; j++)
        {
            d.Term[i * cols + j] = Term[i * cols + j] - b.Term[i * cols + j];
        }
        //To be implemented 
    }
    return d;
}
Matrix Matrix::Sub(Matrix b) {
    Matrix d(rows, cols);
    if (cols != b.cols) cout << "Incompatible matrices" << endl; 
    if (rows != b.rows) cout << "Incompatible matrices" << endl;
       for (int i = 0; i < rows; i++)
        {
           for (int j = 0; j < cols; j++)
            {
                d.Term[i * cols + j] = Term[i * cols + j] - b.Term[i * cols + j];
            }
        }
    return d;
}

Matrix Matrix::Multiply2(Matrix b) {
    if (cols != b.rows) cout << "Incompatible matrices" << endl;
    Matrix bXpose = b.Transpose();
    Matrix d(rows, b.cols);
    d = bXpose.Multiply(Transpose());
    d = d.Transpose();
    
    //  ��ġ����� ���� �̿� AB = (B�� ��ġ * A�� ��ġ)��ġ
    //  Must be implemented by using bXpose  
    return d;
}
    

int Matrix::CompareRowCol(Matrix b) {
    if (cols != b.rows) return 1;
    else return 0;
}
int Matrix::Display() {

    int n;
    n = rows * cols;
    for (int i = 0; i < rows; i++)
    {
        cout << endl;
        for (int j = 0; j < cols; j++)
        {
            cout << Term[i * cols + j] << " ";
        }
        //To be implemented 
    }
    cout << endl;
    return 0;
}

int main()
{
    Matrix a(2, 3);
    Matrix b(3, 4);
    Matrix c(2, 4);
    Matrix d(2, 4);
    Matrix t(4, 3);
    cout << "Enter first matrix: " << endl;
    a.GetData();
    cout << "Enter second matrix: " << endl;
    b.GetData();
    cout << "Display first matrix: " << endl;
    a.Display();
    cout << "Display second matrix : " << endl;
    b.Display();
    t = b.Transpose();
    cout << "Transpose() of Matrix b" << endl;
    t.Display();

    /* If colum of first matrix in not equal to row of second matrix, asking user to enter the size of matrix
again. */
    if (a.CompareRowCol(b))
    {
        cout << "Error! column of first matrix not equal to row of second.";
        cout << "Enter rows and columns for first matrix: ";
    }
    c = a.Multiply(b);//not using transpose()  
    cout << "Multiply of Matrix a,b" << endl;
    c.Display(); //cout << c ; ���� ����
    d = c.Sub(b);
    cout << "Display D : Sub of Matrix c, b" << endl;
    d.Display(); //cout << d ; ���� ����
    cout << "using transpose()" << endl;
    t = b.Transpose();
    c = a.Multiply2(t);//using transpose   
    c.Display(); //cout << c ; ���� ����

    system("pause");
    return 0;
}