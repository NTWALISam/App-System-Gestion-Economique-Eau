import 'package:firebase_database/firebase_database.dart';
import 'package:flutter_application_gestioneauok/db/model.dart';
// refs
final datacloud = FirebaseDatabase.instance.ref(); 

DatabaseReference GestionDeau =datacloud.child("GestionEau");
class UserCrud{
  
static Future createUser(GestionModel usersModel)async{
   //var key=Users.key;
try{
   await GestionDeau.push().set(usersModel.tojson());
}
catch(e){
 print(e);
}
}


/* static Future<UsersModel?> getonUser(keychild) async {
  print('OKOKOK');
  final snap = await GestionDeau.child(keychild).get();
  if (snap.exists) {
   var user = Map<String, dynamic>.from(snap.value) ;
    return UsersModel.formJson(user);
  }
} */


//  static Future updateUser(GestionModel user) async {
//  try {  await GestionDeau.child(user.id_user!).update(user.tojson()).then((_) {
//       print('Update  committed.');
//     });}
//     catch(e){
//       print(e);
//     }
  // }


// static Future deleteUser(UsersModel user) async {
//   try{
//       await GestionDeau.child(user.id_user!).remove().then((_) {
//       print('Transaction  committed.');
//     });
//   }catch(e){
//     print(e);
//   }
//   } 


creatAListener(){
  GestionDeau.onChildAdded.listen((user) { // when child is added
  });

   GestionDeau.onChildChanged.listen((user) { // when child is updated
 
  });

   GestionDeau.onChildRemoved.listen((user) { // when child is removed
  });
} 

}