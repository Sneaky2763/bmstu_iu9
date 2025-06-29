import java.util.Scanner;

public class Points implements Comparable<Points>{
    private int len;
    private int array[][];

    public Points(int[][] arr){
       this.len = arr.length;
       this.array = new int[len][3];
       for(int i=0; i<len; ++i){
           for(int j=0; j<3; ++j){
               this.array[i][j]=arr[i][j];
           }
       }
    }

    public int findVolume(){
        if (len==1){
            return 0;
        }
        int maxX = this.array[0][0];
        int maxY = this.array[0][1];
        int maxZ = this.array[0][2];
        int minX = this.array[0][0];
        int minY = this.array[0][1];
        int minZ = this.array[0][2];
        for(int i=0; i<len; ++i){
            if (this.array[i][0]<minX){
                minX = this.array[i][0];
            }
            if (this.array[i][1]<minY){
                minY = this.array[i][1];
            }
            if (this.array[i][2]<minZ){
                minZ = this.array[i][2];
            }
            if (this.array[i][0]>maxX){
                maxX = this.array[i][0];
            }
            if (this.array[i][1]>maxY){
                maxY = this.array[i][1];
            }
            if (this.array[i][2]>maxZ){
                maxZ = this.array[i][2];
            }
        }
        return (maxX-minX)*(maxY-minY)*(maxZ-minZ);
    }

    public int compareTo(Points a){
        return this.findVolume() - a.findVolume();
    }
    public String toString() {
        String res = "";
        res+="Точки множества:\n";
        for(int i=0; i<len; ++i){
            res+=this.array[i][0];
            res+=" ";
            res+=this.array[i][1];
            res+=" ";
            res+=this.array[i][2];
            res+="\n";
        }
        res+= "Объем параллелепипеда: ";
        res+= this.findVolume();
        res+="\n";
        return res;
    }
}
