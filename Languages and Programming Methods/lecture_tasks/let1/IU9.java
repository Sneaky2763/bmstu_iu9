public class IU9{
        private int group;
        private void getGroup(){
                System.out.println("Group="+group);
        }
        public void setGroup(int n){
                System.out.println("State changed");
                group=n;
        }
        public static void main(String args[]){
                IU9 group1 = new IU9();
                group1.getGroup();
                group1.setGroup(5);
                group1.getGroup();
        }
}
