#include <iostream>

#include "Scene.hh"

using std::cout;
using std::endl;

int main()
{
    srand(time(NULL)); //for random generation

    //---------------Scene build------------------------------
    std::shared_ptr<Scene> scene( new Scene() );

    //---------------Controling------------------------------
    scene->control();

    //---------------Program end------------------------------
    cout << "\n# Summary:" << endl
         << "-Vectors created: " << Vector3D::getCreated() << ". On scene: " << Vector3D::getExisting() << endl
         << "-Drawable objects created: " << Drawable::getCreated() << ". On scene: " << Drawable::getExisting() << endl;

}
