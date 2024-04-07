import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:flutter_application_gestioneauok/screens/HomePage.dart';
//import 'package:flutter_application_gestioneauok/screens/dashboardscreen.dart';
void main() async{
  WidgetsBinding widgetsBinding= await WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp().then((value) {
print("firebse init ok");
  });
runApp(const MaterialApp(
  debugShowCheckedModeBanner: false,
  home: Home(),
));
}
