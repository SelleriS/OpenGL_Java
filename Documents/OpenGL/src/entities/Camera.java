package entities;

import org.lwjgl.input.Keyboard;
import org.lwjgl.util.vector.Vector3f;

public class Camera {

    private Vector3f position = new Vector3f(480f,5,280f);
    private float pitch = 20;
    private float yaw = 0;
    private float roll = 0;

    public Camera() {
    }

    public void move(){ // Key's are in QWERTY!!
        // Commented because keyboard is used for player movements
        if(Keyboard.isKeyDown(Keyboard.KEY_UP)){
            position.x += (float) (Math.sin(Math.toRadians(yaw)));
            position.y -= (float) (Math.sin(Math.toRadians(pitch)));
            position.z += (float) (-Math.cos(Math.toRadians(yaw)));
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_DOWN)){
            position.x -= (float) (Math.sin(Math.toRadians(yaw)));
            position.y += (float) (Math.sin(Math.toRadians(pitch)));
            position.z -= (float) (-Math.cos(Math.toRadians(yaw)));
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_LEFT)){
            yaw-=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_RIGHT)){
            yaw+=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_Q)){
            position.x -= (float) (Math.cos(Math.toRadians(yaw)));
            //position.y -= (float) (Math.cos(Math.toRadians(roll)));
            position.z -= (float) (Math.sin(Math.toRadians(yaw)));
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_W)){
            position.x += (float) (Math.cos(Math.toRadians(yaw)));
            //position.y += (float) (Math.cos(Math.toRadians(roll)));
            position.z += (float) (Math.sin(Math.toRadians(yaw)));
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_Z)){
            position.y+=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_X)){
            position.y-=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_A)){
            pitch-=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_S)){
            pitch+=1f;
        }
        /*if(Keyboard.isKeyDown(Keyboard.KEY_C)){
            roll-=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_V)){
            roll+=1f;
        }*/
        if(Keyboard.isKeyDown(Keyboard.KEY_TAB)){
            pitch = 0;
            yaw = 0;
            roll = 0;
        }
    }

    public Vector3f getPosition() {
        return position;
    }

    public float getPitch() {
        return pitch;
    }

    public float getYaw() {
        return yaw;
    }

    public float getRoll() {
        return roll;
    }
}
