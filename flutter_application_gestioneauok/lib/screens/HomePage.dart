import 'dart:ffi';

import 'package:flutter/material.dart';
import 'package:flutter_application_gestioneauok/db/crud%20rtdb.dart';
import 'package:flutter_application_gestioneauok/db/model.dart';

class Home extends StatefulWidget {
  const Home({Key? key}) : super(key: key);

  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {
  @override
  void initState() {
    // TODO: implement initState 
    super.initState();
    print("Init state");
    GestionDeau.onChildAdded.listen((data) {
      // when child is added
      print(data.snapshot.key);
      setState(() {
        mydata = data.snapshot.value;
      });
    });
    print("after");
    GestionDeau.onChildChanged.listen((data) {
      // when child is changed
      print("On change");
      setState(() {
        mydata = data.snapshot.value;
      });
    });
    // Tronquage de variable

     
  }

  dynamic mydata = {};

  String volume_eau = "";
  String taux = "";
  @override
  Widget build(BuildContext context) {
    // print(mydata['volumeDeau'].toString());

    return Scaffold(
    
      appBar: AppBar(
        title: Text("GESTION EAU"),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Card(
            child: Center(
              child: Column(
                children: [
                  Text(
                    "Volume d'eau: ",
                    style: TextStyle(fontSize: 30),
                  ),
                     SizedBox(
            height: 25,
          ),
                   Text(
                     mydata["volumeDeau"]!=null?
                        mydata["volumeDeau"].toString() +
                        " " +
                        "litres": " " +
                       "0.0" +
                        " " +
                        "litres",
                    style: TextStyle(fontSize: 30),
                  ),
                ],
              ),
            ),
          ),
          SizedBox(
            height: 40,
          ),
          Card(
            child: Center(
              child: Column(
                children: [
                  Text(
                    "Taux De Remplissage: ",
                    
                    style: TextStyle(fontSize: 30),
                  ),
                     SizedBox(
            height: 25,
          ),
                   Text(
                     mydata["tauxDeRemplissage"]!=null?
                        mydata["tauxDeRemplissage"].toString() +
                        " " +
                        "%": 
                       "0.0" +
                        " " +
                        "%",
                    style: TextStyle(fontSize: 30),
                  ),
                ],
              )
            ),
          ),
        ],
      ),
    );
  }
}
