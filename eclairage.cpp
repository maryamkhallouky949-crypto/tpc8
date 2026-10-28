
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

struct Vec3 {
    float x, y, z;

    Vec3(float x, float y, float z)
        : x(x), y(y), z(z) {}
};


float distance3D(const Vec3& a, const Vec3& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

float produitScalaire(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float norme(const Vec3& v) {
    return sqrt(produitScalaire(v, v));
}

Vec3 normaliser(const Vec3& v) {
    float n = norme(v);

    if (n == 0)
        return Vec3(0, 0, 0);

    return Vec3(v.x / n, v.y / n, v.z / n);
}


class Lumiere {
public:
    virtual float intensite(const Vec3& position) const = 0;

    virtual ~Lumiere() {}
};


class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    float couleur;

public:
    LumiereDirectionnelle(Vec3 d, float c)
        : direction(normaliser(d)), couleur(c) {}

    float intensite(const Vec3& position) const override {
        (void)position;
        return couleur;
    }
};

class LumierePonctuelle : public Lumiere {
private:
    Vec3 positionLumiere;
    float attenuation;

public:
    LumierePonctuelle(Vec3 p, float a)
        : positionLumiere(p), attenuation(a) {}

    float intensite(const Vec3& position) const override {
        float d = distance3D(position, positionLumiere);
        return 1.0f / (1.0f + attenuation * d * d);
    }
};

class LumiereSpot : public Lumiere {
private:
    Vec3 positionLumiere;
    Vec3 direction;
    float angleOuverture;

public:
    LumiereSpot(Vec3 p, Vec3 d, float angle)
        : positionLumiere(p),
          direction(normaliser(d)),
          angleOuverture(angle) {}

    float intensite(const Vec3& position) const override {
        Vec3 versPoint(
            position.x - positionLumiere.x,
            position.y - positionLumiere.y,
            position.z - positionLumiere.z
        );

        float d = norme(versPoint);

        if (d == 0)
            return 1.0f;

        versPoint = normaliser(versPoint);

        float cosAngle = produitScalaire(direction, versPoint);

        const float PI = 3.14159265f;
        float limite = cos(angleOuverture * PI / 360.0f);


        if (cosAngle < limite)
            return 0.0f;

  
        return 1.0f / (1.0f + 0.1f * d * d);
    }
};


float calculerEclairage(
    const vector<unique_ptr<Lumiere>>& lumieres,
    const Vec3& point
) {
    float total = 0.0f;

    for (const auto& lumiere : lumieres) {
        total += lumiere->intensite(point);
    }

    return total;
}
int main() {
    vector<unique_ptr<Lumiere>> lumieres;

    lumieres.push_back(
        make_unique<LumiereDirectionnelle>(
            Vec3(0, -1, 0), 0.5f
        )
    );

    lumieres.push_back(
        make_unique<LumierePonctuelle>(
            Vec3(0, 0, 0), 0.2f
        )
    );

    lumieres.push_back(
        make_unique<LumiereSpot>(
            Vec3(0, 0, 5), Vec3(0, 0, -1), 60.0f
        )
    );

    Vec3 points[] = {
        Vec3(0, 0, 1),
        Vec3(2, 0, 0),
        Vec3(0, 0, 10)
    };

    for (int i = 0; i < 3; i++) {
        cout << "Point " << i + 1 << " : ("
             << points[i].x << ", "
             << points[i].y << ", "
             << points[i].z << ")" << endl;

        cout << "Eclairage total = "
             << calculerEclairage(lumieres, points[i])
            
            << endl << endl;            
            }
    return 0;
}
