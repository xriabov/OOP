#include <iostream>
#include <cmath>

class Vector2D
{
    private:
    double x, y;

    public:
    double X() { return x; }
    double Y() { return y; }

    void Print()
    {
        std::cout << "(" << x << ", " << y << ")";
    }

    Vector2D (double xVal = 0, double yVal = 0)
    {
        x = xVal;
        y = yVal;
    }

    Vector2D operator + (double scalar)
    {
        Vector2D out(x + scalar, y + scalar);
        return out;
    }
    Vector2D operator + (Vector2D &vect)
    {
        Vector2D out(x + vect.X(), y + vect.Y());
        return out;
    }
    Vector2D operator - (double scalar)
    {
        Vector2D out(x - scalar, y - scalar);
        return out;
    }
    Vector2D operator - (Vector2D &vect)
    {
        Vector2D out(x - vect.X(), y - vect.Y());
        return out;
    }
    Vector2D operator / (double scalar)
    {
        Vector2D out(x/scalar, y/scalar);
        return out;
    }
    double operator * (Vector2D &vect)
    {
        return x * vect.X() + y * vect.Y();
    }

    double Length()
    {
        return sqrt(x*x + y*y);
    }
};

class Vector3D
{
    private:
    double x, y, z;

    public:
    double X() { return x; }
    double Y() { return y; }
    double Z() { return z; }

    void Print()
    {
        std::cout << "(" << x << ", " << y << ", " << z << ")";
    }

    Vector3D (double xVal = 0, double yVal = 0, double zVal = 0)
    {
        x = xVal;
        y = yVal;
        z = zVal;
    }

    Vector3D operator + (double scalar)
    {
        double newX = x + scalar;
        double newY = y + scalar;
        double newZ = z + scalar;

        Vector3D out(newX, newY, newZ);

        return out;
    }
    Vector3D operator + (Vector3D &vect)
    {
        Vector3D out(x + vect.X(), y + vect.Y(), z + vect.Z());
        return out;
    }
    Vector3D operator - (double scalar)
    {
        double newX = x - scalar;
        double newY = y - scalar;
        double newZ = z - scalar;

        Vector3D out(newX, newY, newZ);

        return out;
    }
    Vector3D operator - (Vector3D &vect)
    {
        Vector3D out(x - vect.X(), y - vect.Y(), z - vect.Z());
        return out;
    }
    Vector3D operator / (double scalar)
    {
        Vector3D out(x/scalar, y/scalar, z/scalar);
        return out;
    }
    Vector3D operator * (Vector3D &vect)
    {
        double newX = y*vect.Z() - z*vect.Y();
        double newY = z*vect.X() - x*vect.Z();
        double newZ = x*vect.Y() - y*vect.X();

        Vector3D out(newX, newY, newZ);
        
        return out;
    }
    double Length()
    {
        return sqrt(x*x + y*y + z*z);
    }
};

class Polygon2D
{
    private:
        int vectLen;
        Vector2D* vectors;
    public:
        int VectLen() { return vectLen; }
        Vector2D* Vectors() { return vectors; }

        Polygon2D(int len, Vector2D *vect)
        {
            vectLen = len;
            vectors = new Vector2D[vectLen];

            for(int i = 0; i < vectLen; i++)
                vectors[i] = vectors[i] + vect[i];
        }
        ~Polygon2D() { delete[] vectors; }

        Polygon2D operator = (Polygon2D &poly)
        {
            Polygon2D out(poly.VectLen(), poly.Vectors());
            return out;
        }

        double Perimeter()
        {
            double P(0);
            Vector2D tmp;
            for(int i = 0; i < vectLen-1; i++)
            {
                tmp = vectors[i+1] - vectors[i];
                P += tmp.Length();
            }
            
            tmp = vectors[0] - vectors[vectLen-1];
            P += tmp.Length();

            return P;
        }

        double Area()
        {
            double area(0);

            if (vectLen < 3) 
                return 0;

            for (int i=1; i<vectLen-1; i++)
                area += vectors[i].X() * vectors[i+1].Y() - vectors[i].Y() * vectors[i+1].X();
            
            area += vectors[vectLen-1].X() * vectors[0].Y() - vectors[vectLen].Y() * vectors[0].X();
            return area / 2.0;
        }

        Vector2D Center()
        {
            Vector2D center = Vector2D(0, 0);
            for(int i = 0; i < vectLen; i++)
                center = center + vectors[i];

            return center/vectLen;
        }
};

class Polygon3D
{
    private:
        int vectLen;
        Vector3D* vectors;
    public:
        int VectLen() { return vectLen; }
        Vector3D* Vectors() { return vectors; }

        Polygon3D(int len, Vector3D* vect)
        {
            vectLen = len;
            vectors = new Vector3D[vectLen];
            for(int i = 0; i < vectLen; i++)
                vectors[i] = vectors[i] + vect[i];
        }
        ~Polygon3D() { delete[] vectors; }

        Polygon3D operator = (Polygon3D &poly)
        {
            Polygon3D out(poly.VectLen(), poly.Vectors());
            return out;
        }

        double Perimeter()
        {
            double P(0);
            Vector3D tmp;
            for(int i = 0; i < vectLen-1; i++)
            {
                tmp = vectors[i+1] - vectors[i];
                P += tmp.Length();
            }

            tmp = vectors[0] - vectors[vectLen-1];
            P += tmp.Length();

            return P;
        }

        Vector3D Center()
        {
            Vector3D center = Vector3D(0, 0, 0);
            for(int i = 0; i < vectLen; i++)
                center = center + vectors[i];

            return center/vectLen;
        }
};


int main()
{
    Vector2D vect[4];
    vect[0] = Vector2D(0,0);
    vect[1] = Vector2D(10,0);
    vect[2] = Vector2D(10,1);
    vect[3] = Vector2D(0,1);


    Polygon2D poly(4, vect);

    std::cout << poly.Area() << std::endl;

    return 0;
}
