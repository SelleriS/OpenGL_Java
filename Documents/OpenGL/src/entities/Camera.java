package entities;

import org.lwjgl.input.Keyboard;
import org.lwjgl.util.vector.Vector3f;

public class Camera {

    private Vector3f position = new Vector3f(480f,5,280f);
    private float pitch=10;
    private float yaw =200;
    private float roll;

    public Camera() {
    }

    public void move(){ // Key are in QWERTY!!
        if(Keyboard.isKeyDown(Keyboard.KEY_DOWN)){
            position.z-=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_UP)){
            position.z+=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_LEFT)){
            position.x+=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_RIGHT)){
            position.x-=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_Z)){
            position.y+=1f;
        }
        if(Keyboard.isKeyDown(Keyboard.KEY_X)){
            position.y-=1f;
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
