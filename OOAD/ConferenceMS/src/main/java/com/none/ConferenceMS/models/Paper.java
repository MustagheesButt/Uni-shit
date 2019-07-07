package com.none.ConferenceMS.models;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Lob;

@Entity
public class Paper {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    int id;

    @Lob
    byte[] file;
    String fileName;
    String fileType;

    String title;
    int status;
    int submittedBy;
    int reviewedBy;

    public Paper() {
        
    }

    public Paper(String title, byte[] file, String fileName, String fileType) {
        this.setTitle(title);
        this.setFile(file);
        this.setFileName(fileName);
        this.setFileType(fileType);
    }

    public Paper(int id, String title, byte[] file, String fileName, String fileType) {
        this.setId(id);
        this.setTitle(title);
        this.setFile(file);
        this.setFileName(fileName);
        this.setFileType(fileType);
    }
    
    public int getId() {
        return this.id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTitle() {
        return this.title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public byte[] getFile() {
        return this.file;
    }

    public void setFile(byte[] file) {
        this.file = file;
    }

    public String getFileName() {
        return this.fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getFileType() {
        return this.fileType;
    }

    public void setFileType(String fileType) {
        this.fileType = fileType;
    }

    public int getStatus() {
        return this.status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public int getSubmittedBy() {
        return this.submittedBy;
    }

    public void setSubmittedBy(int submittedBy) {
        this.submittedBy = submittedBy;
    }

    public int getReviewedBy() {
        return this.reviewedBy;
    }

    public void setReviewedBy(int reviewedBy) {
        this.reviewedBy = reviewedBy;
    }
}