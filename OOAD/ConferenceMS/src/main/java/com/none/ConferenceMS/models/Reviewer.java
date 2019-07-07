package com.none.ConferenceMS.models;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Reviewer {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    int id;

    String firstName;
    String lastName;
    String email;
    String password;
    String phone;

    public Reviewer() {
        
    }

    public Reviewer(String fn, String ln, String email, String pwd, String phone) {
        this.setFirstName(fn);
        this.setLastName(ln);
        this.setEmail(email);
        this.setPassword(pwd);
        this.setPhone(phone);
    }

    public Reviewer(int id, String fn, String ln, String email, String pwd, String phone) {
        this.setId(id);
        this.setFirstName(fn);
        this.setLastName(ln);
        this.setEmail(email);
        this.setPassword(pwd);
        this.setPhone(phone);
    }
    
    public int getId() {
        return this.id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getFirstName() {
        return this.firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return this.lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getEmail() {
        return this.email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return this.password;
    }

    public void setPassword(String password) {
        // TODO: encrypt password
        this.password = password;
    }

    public String getPhone() {
        return this.phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

}