package enigineTester;

import entities.Camera;
import entities.Entity;
import entities.Light;
import models.TexturedModel;
import org.lwjgl.opengl.Display;
import org.lwjgl.util.vector.Vector3f;
import renderEngine.*;
import models.RawModel;
import shaders.StaticShader;
import terrains.Terrain;
import textures.ModelTexture;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class MainGameLoop {

    public static void main(String[] args){

        DisplayManager.createDisplay();
        Loader loader = new Loader();

        RawModel model = OBJLoader.loadObjModel("dragon", loader);
        TexturedModel staticModel = new TexturedModel(model, new ModelTexture(loader.loadTexture("image2")));
        Entity testEntity = new Entity(staticModel, new Vector3f(500f,0f,300f),0,0,0,5);

        RawModel treeModel = OBJLoader.loadObjModel("tree", loader);
        TexturedModel tree = new TexturedModel(treeModel, new ModelTexture(loader.loadTexture("tree")));
        RawModel grassModel = OBJLoader.loadObjModel("grassModel", loader);
        TexturedModel grass = new TexturedModel(grassModel, new ModelTexture(loader.loadTexture("grassTexture")));
        grass.getTexture().setHasTransparency(true);
        grass.getTexture().isUseFakeLighting();
        RawModel fernModel = OBJLoader.loadObjModel("fern", loader);
        TexturedModel fern = new TexturedModel(fernModel, new ModelTexture(loader.loadTexture("fern")));
        fern.getTexture().setHasTransparency(true);
        fern.getTexture().isUseFakeLighting();

        // To add 500 randomly placed trees, grass and fern in the open world
        List<Entity> entities = new ArrayList<>();
        Random random = new Random();
        for(int i = 0; i < 1000; i++){
            entities.add(new Entity(tree, new Vector3f(random.nextFloat() * 1500 + 50, 0,
                    random.nextFloat() * 1500 + 50), 0, 0, 0, 3));
            entities.add(new Entity(grass, new Vector3f(random.nextFloat() * 1500 + 50, 0,
                    random.nextFloat() * 1500 + 50), 0, 0, 0, 1));
            entities.add(new Entity(fern, new Vector3f(random.nextFloat() * 1500 + 50, 0,
                    random.nextFloat() * 1500 + 50), 0, 0, 0, 0.6f));
        }


        //To set sine and reflectivity
        //ModelTexture texture = staticModel.getTexture();
        //texture.setShineDamper(10);
        //texture.setReflectivity(1);

        Light light = new Light(new Vector3f(3000,2000,2000), new Vector3f(1,1,1));

        //Generate terrain
        List<Terrain> terrains = new ArrayList<>();
        for(int x = 0; x < 2; x++){
            for(int z = 0; z < 2; z++){
                terrains.add( new Terrain(x,z, loader, new ModelTexture(loader.loadTexture("grass"))));
            }
        }

        Camera camera = new Camera();

        MasterRenderer renderer = new MasterRenderer();
        while(!Display.isCloseRequested()){
            camera.move();
            //entity.increaseRotation(0, 1, 0);
            renderer.processEntity(testEntity);

            for(Terrain terrain:terrains){
                renderer.processTerrain(terrain);
            }

            for(Entity entity:entities){
                renderer.processEntity(entity);
            }

            renderer.render(light, camera);
            DisplayManager.updateDisplay();
        }

        renderer.cleanUp();
        loader.cleanUp();
        DisplayManager.closeDisplay();

    }
}
